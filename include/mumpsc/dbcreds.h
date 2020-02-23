#ifndef DBCREDS_H
#define DBCREDS_H
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
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+
 *#+	The btree array handler calls these functions to get database
 *#+    credentials from the user.
 *#+
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define DBCRED_MAX_LENGTH 128

class DBCredentials {

public:
    enum DBCredentialsError {
        DBCRED_ERROR_DISABLING_ECHO,
        DBCRED_ERROR_IN_STD_CIN,
        DBCRED_ERROR_IN_GETLOGIN_R,
        DBCRED_NUM_ERRORS
    };
    static DBCredentials& getInstance();
    bool getError(DBCredentialsError error) const;
    bool fail() const;
    char* getDatabase();
    const char* getUser();
    const char* getPassword();

protected:
    void printErrors();
    /**
     * It is assumed that buffer is of size DBCRED_MAX_LENGTH.
     */
    void getInput(const char* prompt, bool isPassword, char* buffer);
    /**
     * It is assumed that buffer is of size DBCRED_MAX_LENGTH.
     */
    void getOSUsername(char* buffer);

private:
    unsigned int flags;
    bool gotDatabase;
    char dbname[DBCRED_MAX_LENGTH];
    bool gotUser;
    char user[DBCRED_MAX_LENGTH];
    bool gotPassword;
    char passwd[DBCRED_MAX_LENGTH];
    DBCredentials();
    DBCredentials(const DBCredentials&);
    void operator=(const DBCredentials&);
    void setError(DBCredentialsError error);
    void clearErrors();

};

#endif
