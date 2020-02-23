/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+	Database Credential User Prompt Functions
 *#+	Copyright (c) A.D. 2020 by David Tsai
 *#+	tsai@nyu.edu
 *#+	david@wecsam.com
 *#+
 *#+	This library is free software; you can redistribute it and/or
 *#+	modify it under the terms of the GNU Lesser General Public
 *#+	License as published by the Free Software Foundation; either
 *#+	version 2.1 of the License, or (at your option) any later version.
 *#+
 *#+	This library is distributed in the hope that it will be useful,
 *#+	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *#+	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *#+	Lesser General Public License for more details.
 *#+
 *#+    You should have received a copy of the GNU Lesser General Public
 *#+	License along with this library; if not, write to the Free Software
 *#+	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <mumpsc/dbcreds.h>
#include <cstring>
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

DBCredentials& DBCredentials::getInstance() {
    static DBCredentials instance;
    return instance;
}

bool DBCredentials::getError(DBCredentialsError error) const {
    return flags & (1 << error);
}

bool DBCredentials::fail() const {
    return flags;
}

char* DBCredentials::getDatabase() {
    if (!gotDatabase) {
        cout << "Using username as database name.\n";
        gotDatabase = true;
    }
    // Return a non-const copy because sql() wants one.
    strcpy(dbname, getUser());
    return dbname;
}

const char* DBCredentials::getUser() {
    if (!gotUser) {
        getOSUsername(user);
        if (fail()) {
            printErrors();
            getInput("Enter DB username", false, user);
            if (fail()) {
                printErrors();
                return "";
            }
        } else {
            cout << "Using DB username: " << user << '\n';
        }
        gotUser = true;
    }
    return user;
}

const char* DBCredentials::getPassword() {
    if (!gotPassword) {
        getInput("Enter DB password", true, passwd);
        if (fail()) {
            printErrors();
            return "";
        }
        gotPassword = true;
    }
    return passwd;
}

void DBCredentials::printErrors() {
    if (getError(DBCRED_ERROR_DISABLING_ECHO)) {
        cerr << "Terminal echo could not be disabled to hide password input.\n";
    }
    if (getError(DBCRED_ERROR_IN_STD_CIN)) {
        cerr << "The standard input stream failed.\n";
    }
    if (getError(DBCRED_ERROR_IN_GETLOGIN_R)) {
        cerr << "The Linux username could not be obtained.\n";
    }
}

void DBCredentials::getInput(const char* prompt, bool isPassword, char* buffer) {
    termios termiosOld, termiosNew;

    clearErrors();
    strcpy(buffer, "");

    cout << prompt << " (max " << DBCRED_MAX_LENGTH << " chars): ";
    cout.flush();

    if (isPassword) {
        // Disable echoing.
        if (tcgetattr(0, &termiosOld) != 0) {
            setError(DBCRED_ERROR_DISABLING_ECHO);
            return;
        }
        termiosNew = termiosOld;
        termiosNew.c_lflag &= ~ECHO;
        if (tcsetattr (0, TCSAFLUSH, &termiosNew) != 0) {
            setError(DBCRED_ERROR_DISABLING_ECHO);
            return;
        }
    }

    cin.getline(buffer, DBCRED_MAX_LENGTH);
    if (cin.fail()) {
        strcpy(buffer, "");
        setError(DBCRED_ERROR_IN_STD_CIN);
    }

    if (isPassword) {
        cout << endl;
        // Re-enable echoing.
        tcsetattr(0, TCSAFLUSH, &termiosOld);
    }
}

void DBCredentials::getOSUsername(char* buffer) {
    clearErrors();
    strcpy(buffer, "");

    if (getlogin_r(buffer, DBCRED_MAX_LENGTH) != 0) {
        setError(DBCRED_ERROR_IN_GETLOGIN_R);
    }
}

DBCredentials::DBCredentials() :
    flags(0), gotDatabase(false), gotUser(false), gotPassword(false) {}

void DBCredentials::setError(DBCredentialsError error) {
    flags |= (1 << error);
}

void DBCredentials::clearErrors() {
    flags = 0;
}
