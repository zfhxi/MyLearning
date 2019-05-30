/*  
use sales

-- create table agents
create table agents
(
    aid char(3) not null,
    aname varchar(50),
    city varchar(50),
    [percent]float
        primary key(aid)
)
use sales

-- create table agents
create table orders
(
    ordno char(4) not null,
    month varchar(12),
    cid char(4) not null,
    aid char(3) not null,
    pid char(3) not null,
    qty float,
    dollars float
        primary key(ordno)
)
*/
use sales

-- copy structure of orders to test1 and agents to test2
select*into test1 from orders where 1=2
select*into test2 from agents where 1=2