drop table if exists temps;

create table temps ( city varchar(32), temp int, dewpt int);

insert into temps values ('Boston', '32', '25');
insert into temps values ('Hyannis', '42', '32');
insert into temps values ('Norwood', '32', '12');
insert into temps values ('Quincy', '32', '24');
insert into temps values ('Waltham', '28', '23');

drop view if exists mtemps;

create view mtemps (gbl,a1,a2,a3,a4) as select 'mtemps' as gbl, city as a1, temp as a2, dewpt as a3, '' as a4 from temps;

select * from mtemps;
