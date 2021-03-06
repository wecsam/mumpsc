/* map mumps globals to RDBMS PostgreSQL compatible version */

create temporary view lab_table as select a1 as test_code, a2 as test_name, a3 as low, a4 as high from labtab;

create temporary view lab_rslts as select a1 as ptid, a2 as test, a3 as date, a4 as time, a5 as rslt from labs;

create temporary view problem_table as select a1 as icd, a2 as dx from probtab;

create temporary view problem_list as select a1 as ptid, a2 as icd, a3 as onset, a4 as resolved from problems;

create temporary view med_table as select a1 as medcode, a2 as lowdose, a3 as highdose, a4 as med_name from medtab;

create temporary view med_admin as select a1 as ptid, a2 as medcode, a3 as dose, a4 as date, a5 as time from medadmin;

create temporary view patient_id as select a1 as ptid, a2 as date, a3 as time, a4 as street, a5 as citystate, a6 as zip, a7 as tel, a8 as insurer from patientid;

create temporary view pt_name as select a1 as ptid, a2 as name from ptname;

create temporary view pt_namex as select a1 as ptid, a2 as name, select test 'empty' as a3 from ptname;

create temporary view vital_signs as select a1 as ptid, a2 as date, a3 as time, a4 as sys, a5 as dia, a6 as resp, a7 as temp from vitals;

select * from lab_table limit 10;
select * from lab_rslts limit 10;
select * from problem_table limit 10;
select * from problem_list limit 10;
select * from med_table limit 10;
select * from med_admin limit 10;
select * from patient_id limit 10;
select * from pt_name limit 10;
select * from vital_signs limit 10;

select patient_id.ptid, pt_name.name, lab_table.test_name 
from pt_name,patient_id,lab_table,lab_rslts 
where patient_id.ptid = lab_rslts.ptid and pt_name.ptid=patient_id.ptid and lab_rslts.test = lab_table.test_code;
