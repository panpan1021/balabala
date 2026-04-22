#第11章_数据处理之增删改

#0. 储备工作
USE atguigudb;

CREATE TABLE IF NOT EXISTS emp1(
id INT,
`name` VARCHAR(15),
hire_date DATE,
salary DOUBLE(10,2)
);

DESC emp1;

SELECT *
FROM emp1;

#1. 添加数据

#方式1：一条一条的添加数据

# ① 没有指明添加的字段
#正确的
INSERT INTO emp1
VALUES (1,'Tom','2000-12-21',3400); #注意：一定要按照声明的字段的先后顺序添加
#错误的
INSERT INTO emp1
VALUES (2,3400,'2000-12-21','Jerry');

# ② 指明要添加的字段 （推荐）
INSERT INTO emp1(id,hire_date,salary,`name`)
VALUES(2,'1999-09-09',4000,'Jerry');
# 说明：没有进行赋值的hire_date 的值为 null
INSERT INTO emp1(id,salary,`name`)
VALUES(3,4500,'shk');

# ③ 同时插入多条记录 （推荐）
INSERT INTO emp1(id,NAME,salary)
VALUES
(4,'Jim',5000),
(5,'张俊杰',5500);

#方式2：将查询结果插入到表中

SELECT * FROM emp1;

INSERT INTO emp1(id,NAME,salary,hire_date)
#查询语句
SELECT employee_id,last_name,salary,hire_date  # 查询的字段一定要与添加到的表的字段一一对应
FROM employees
WHERE department_id IN (70,60);

DESC emp1;
DESC employees;

#说明：emp1表中要添加数据的字段的长度不能低于employees表中查询的字段的长度。
# 如果emp1表中要添加数据的字段的长度低于employees表中查询的字段的长度的话，就有添加不成功的风险。

#2. 更新数据 （或修改数据）
# UPDATE .... SET .... WHERE ...
# 可以实现批量修改数据的。

UPDATE emp1
SET hire_date = CURDATE()
WHERE id = 5;

SELECT * FROM emp1;

#同时修改一条数据的多个字段
UPDATE emp1
SET hire_date = CURDATE(),salary = 6000
WHERE id = 4;

#题目：将表中姓名中包含字符a的提薪20%
UPDATE emp1
SET salary = salary * 1.2
WHERE NAME LIKE '%a%';

#修改数据时，是可能存在不成功的情况的。（可能是由于约束的影响造成的）
UPDATE employees
SET department_id = 10000
WHERE employee_id = 102;

#3. 删除数据 DELETE FROM .... WHERE....

DELETE FROM emp1
WHERE id = 1;

#在删除数据时，也有可能因为约束的影响，导致删除失败
DELETE FROM departments
WHERE department_id = 50;

#小结：DML操作默认情况下，执行完以后都会自动提交数据。
# 如果希望执行完以后不自动提交数据，则需要使用 SET autocommit = FALSE.

#4. MySQL8的新特性：计算列
USE atguigudb;

CREATE TABLE test1(
a INT,
b INT,
c INT GENERATED ALWAYS AS (a + b) VIRTUAL  #字段c即为计算列
);

INSERT INTO test1(a,b)
VALUES(10,20);

SELECT * FROM test1;

UPDATE test1
SET a = 100;

#5.综合案例
# 1、创建数据库test01_library
CREATE DATABASE IF NOT EXISTS test01_library CHARACTER SET 'utf8';

USE test01_library;

# 2、创建表 books，表结构如下：
CREATE TABLE IF NOT EXISTS books(
id INT,
`name` VARCHAR(50),
`authors` VARCHAR(100),
price FLOAT,
pubdate YEAR,
note VARCHAR(100),
num INT
);

DESC books;

SELECT * FROM books;
# 3、向books表中插入记录

# 1）不指定字段名称，插入第一条记录
INSERT INTO books
VALUES(1,'Tal of AAA','Dickes',23,'1995','novel',11);
# 2）指定所有字段名称，插入第二记录
INSERT INTO books(id,NAME,AUTHORS,price,pubdate,note,num)
VALUES(2,'EmmaT','Jane lura',35,'1993','joke',22);
# 3）同时插入多条记录（剩下的所有记录）
INSERT INTO books(id,NAME,AUTHORS,price,pubdate,note,num)
VALUES
(3,'Story of Jane','Jane Tim',40,2001,'novel',0),
(4,'Lovey Day','George Byron',20,2005,'novel',30),
(5,'Old land','Honore Blade',30,2010,'Law',0),
(6,'The Battle','Upton Sara',30,1999,'medicine',40),
(7,'Rose Hood','Richard haggard',28,2008,'cartoon',28);


# 4、将小说类型(novel)的书的价格都增加5。
UPDATE books
SET price = price + 5
WHERE note = 'novel';

SELECT * FROM books;



SELECT NAME FROM books;
SELECT REPLACE (NAME,' ','')
FROM books;

SELECT NAME "shuming",note,CASE note WHEN 'novel' THEN 'xiaoshuo'



SELECT NAME AS "shuming" ,num AS "库存",CASE WHEN num>30 THEN 'hzixiao'
					     WHEN num>0 AND num<10 THEN 'das'
					     WHEN num=0 THEN 'das'
					     ELSE 'dasfrs'
					     END "xianshizhaun"
					     
					     	



SELECT IFNULL(note,'合计') AS note,SUM(num)
FROM books
GROUP BY note WITH ROLLUP;


CREATE DATABASE IF NOT EXISTS dbtest1 CHARACTER SET 'utf8';
SHOW CREATE DATABASE dbtest1;

CREATE TABLE temp(
id INT
)CHARACTER SET 'gdk';

SHOW VARIABLES LIKE 'character_%';


-- 1
SELECT last_name,e.`department_id`,department_name
FROM employees e JOIN departments d
ON e.`department_id`=d.`department_id`;
-- 2
SELECT job_id,location_id
FROM employees e,departments d
WHERE e.`department_id`=90 AND d.`department_id`=90;

SELECT * FROM employees;

SELECT * FROM departments;

SELECT e.last_name,d.department_name,l.location_id,city 
FROM employees e,locations l,departments d
WHERE e.`salary` IS NOT NULL
AND e.`department_id`=d.`department_id`
AND d.`location_id`=l.`location_id`;


SELECT e.last_name,e.job_id,d.department_id,d.department_name
FROM employees e JOIN  departments d
ON e.`department_id`=d.`department_id`
JOIN locations l
ON l.`location_id`=d.`location_id` AND l.`city`='Toronto';


SELECT d.department_name,l.location_id,e.last_name,e.job_id,e.salary 
FROM employees e JOIN departments d
ON e.`department_id`=d.`department_id` AND d.`department_name`='executive'
JOIN locations l
ON l.`location_id`=d.`location_id`


SELECT e1.last_name,e1.employee_id,e1.manager_id,e2.last_name,e2.employee_id
FROM employees e1 JOIN  employees e2
ON e1.manager_id=e2.employee_id;

SELECT d.department_name 
FROM departments d 
WHERE NOT EXISTS (
    SELECT 1 
    FROM employees e 
    WHERE e.department_id = d.department_id
);


SELECT department_id
FROM departments d LEFT JOIN employees e
ON e.`department_id`=d.`department_id`
WHERE e.`department_id`<=> NULL;


SELECT l.`city`
FROM locations l LEFT JOIN departments d
ON l.`location_id`=d.`location_id`
WHERE d.location_id IS NULL;



SELECT e.employee_id,e.last_name
FROM employees e JOIN departments d
ON e.`department_id`=d.`department_id`
AND d.`department_name` IN ('sales','it');












