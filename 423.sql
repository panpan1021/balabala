CREATE TABLE test_enum(
season ENUM ('春','夏','秋','冬')
);
INSERT INTO test_enum VALUES('春');

INSERT INTO test_enum VALUES(2);

SELECT * FROM test_enum;

SELECT DATABASE();\
SELECT USER();


CREATE TABLE test_set(
s SET('A','B','C')
);
INSERT INTO test_set (s) VALUES ('A'),('A,B');
SELECT * FROM test_set;


CREATE TABLE test_json (
js json
);
INSERT INTO test_json (js)
VALUES ('{"name":"songhk","fuck":"dasad","daada":{"provin":"dasda"}}');



SELECT js->'$.name' NAME,js->'$.fuck' FROM test_json;



CREATE TABLE test2(
id INT UNIQUE,
last_name VARCHAR(15),
email VARCHAR(25) UNIQUE,
salary DECIMAL(10,2),

CONSTRAINT uk_test2_email UNIQUE(email)
);


DESC test2;

SELECT * FROM information_schema.`TABLE_CONSTRAINTS`
WHERE table_name='test2';


INSERT INTO test2(id,last_name,email,salary)
VALUES (3,'tom',NULL,4600);


ALTER TABLE test2 
DROP INDEX email;


CREATE TABLE test5(
id INT ,
last_name VARCHAR(11),
CONSTRAINT pp PRIMARY KEY (id)
);


CREATE TABLE test7(
id INT PRIMARY KEY AUTO_INCREMENT,
NAME VARCHAR(22) 
);
INSERT INTO test7(NAME)
VALUES('tmom');

SELECT * FROM test7;


CREATE TABLE dept1(
dept_id INT,
dept_name VARCHAR(15)
);



ALTER TABLE dept1
ADD PRIMARY KEY (dept_id);





CREATE TABLE test11(
emp_id INT PRIMARY KEY AUTO_INCREMENT,
emp_name VARCHAR(15),
department_id INT,

CONSTRAINT fk FOREIGN KEY (department_id) REFERENCES dept1(dept_id)
);

SELECT * FROM information_schema.`TABLE_CONSTRAINTS`
WHERE table_name='test11';


DESC emp1;

SHOW CREATE TABLE emp1;

SELECT DATABASE();




















