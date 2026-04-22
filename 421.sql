SELECT last_name,salary FROM employees WHERE salary BETWEEN 5000 AND 12000;
SELECT last_name,salary FROM employees WHERE salary NOT BETWEEN 5000 AND 12000;

SELECT last_name,department_id FROM employees WHERE department_id IN (20,50);

SELECT last_name,job_id FROM employees WHERE manager_id IS NULL;

SELECT last_name,salary,commission_pct FROM employees WHERE salary IS NOT NULL;

SELECT last_name FROM employees WHERE last_name LIKE '__a%';

SELECT last_name FROM employees WHERE last_name LIKE '%a%k%' OR last_name LIKE '%k%a%';

SELECT * FROM employees ;

SELECT last_name,salary FROM employees ORDER BY salary;


SELECT last_name,salary FROM employees ORDER BY salary DESC;

-- 猎德别名只能在order by中使用
SELECT employee_id,salary,salary*12 annual_sal
FROM employees ORDER BY annual_sal;

SELECT * FROM employees LIMIT 2,20;

SELECT employee_id,last_name,salary FROM employees ORDER BY salary DESC LIMIT 10;


SELECT employee_id,last_name FROM employees LIMIT 31,2;

SELECT * FROM employees LIMIT 2 OFFSET 31;

SELECT employee_id,department_name FROM employees,departments;

SELECT employee_id,deprentment_name FROM employees,departments WHERE employees.`department_id`=departments.`department_id`;

SELECT * FROM employees;
SELECT emp.employee_id,emp.last_name FROM employees emp,employees mgr
WHERE emp.`manager_id`=mgr.`employee_id`;


SELECT last_name,department_name FROM employees e JOIN departments d
ON e.`department_id`=d.`department_id` JOIN  locations l ON
d.`location_id`=l.`location_id`;


SELECT last_name ,department_name FROM employees e JOIN departments d
ON e.`department_id`=d.`department_id`;

SELECT last_name ,department_name FROM employees e LEFT  JOIN departments d
ON e.`department_id`=d.`department_id`;
-- 满外连接怎么实现???
-- union会执行去重,union all不会执行去重
SELECT employee_id,department_name FROM employees e JOIN 



SELECT ABS(-23),ABS(33),SIGN(42),SIGN(-1),PI(),CEILING(3.5),FLOOR(-42.453);


SELECT RAND(),RAND(39),RAND(-1) ;

SELECT ROUND(3242.42342,-2);

SELECT TRUNCATE(123.342,0);

SELECT POW(2,5),POWER


SELECT ASCII ('dsaasd'),CHAR_LENGTH('feafa'),CHAR_LENGTH('大擦'),LENGTH('das'),LENGTH('打算');


SELECT INSERT('helloworld',2,3,'aaaaa'),REPLACE('hello','lo','mmm');

SELECT UPPER('dasda'),LOWER('dSADCAS');

SELECT RIGHT('dasdas',4);


SELECT employee_id,last_name ,LPAD(salary,10,'&') FROM employees;


SELECT LENGTH(TRIM('       adf    as    '));

SELECT REPEAT('dasd',4);

SELECT SPACE(3);

SELECT SUBSTR('fdscasd',2,3);


SELECT  USER();

