
USE atguigudb;
SELECT employee_id,last_name,department_id FROM employees;
SELECT employee_id emp_id,last_name lname,department_id FROM employees;

SELECT DISTINCT department_id FROM employees;
SELECT DISTINCT department_id,salary FROM employees;

SELECT * FROM employees;

SELECT employee_id,salary "月工资",salary*(1+commission_pct)*12 "年工资" FROM employees;
SELECT employee_id,salary "月工资",salary*(1+IFNULL(commission_pct,0))*12 "年工资" FROM employees;


SELECT * FROM `order`;


SELECT "dasas", 213,employee_id,last_name FROM employees;

DESCRIBE employees;-- 显示表中信息

DESC departments;


SELECT * FROM employees WHERE department_id=89;

SELECT * FROM employees WHERE last_name ='King';


SELECT employee_id,last_name,salary*12 "annual salary"
FROM employees;
SELECT DISTINCT job_id
FROM employees;


SELECT 100,100+2,100-8,23+432.23;

SELECT 200+'2';


SELECT 299+'234';

SELECT 299/3,100 DIV 0;


SELECT 1='1',1=0,0='a';

SELECT 'a'='das';

SELECT 1=NULL;


SELECT 1+NULL;

SELECT NULL=NULL;

SELECT NULL<=>NULL;

SELECT NULL<>NULL;

SELECT last_name,salary FROM employees WHERE commission_pct <=>NULL;

SELECT * FROM employees WHERE commission_pct IS  NULL;

SELECT * FROM employees WHERE ISNULL(commission_pct,1); 

SELECT * FROM employees WHERE NOT commission_pct<=> NULL;

SELECT LEAST('g','b','t','dda');
SELECT GREATEST('g','b','t','dda');

SELECT LEAST(LENGTH(first_name),LENGTH(last_name)) FROM employees;

SELECT employee_id,last_name,salary FROM employees WHERE salary BETWEEN 4444 AND 88888--


-- or in like _ %

SELECT last_name FROM employees WHERE last_name LIKE '_\_a%';

SELECT last_name FROM employees WHERE last_name LIKE '_$_a%' ESCAPE '$';

-- 逻辑运算符 or and not xor && ||





