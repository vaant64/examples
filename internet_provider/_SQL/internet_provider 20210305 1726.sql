-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.5.25


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema internet_provider
--

CREATE DATABASE IF NOT EXISTS internet_provider;
USE internet_provider;

--
-- Definition of table `contract`
--

DROP TABLE IF EXISTS `contract`;
CREATE TABLE `contract` (
  `ID_C` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `CPassport` varchar(10) NOT NULL,
  `CFName` varchar(32) NOT NULL,
  `CLName` varchar(32) NOT NULL,
  `CMName` varchar(32) NOT NULL,
  `CSex` varchar(1) NOT NULL,
  `CBirthday` date NOT NULL,
  `CAddress` varchar(128) NOT NULL,
  `CFDate` date NOT NULL,
  `CLDate` date DEFAULT NULL,
  PRIMARY KEY (`ID_C`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `contract`
--

/*!40000 ALTER TABLE `contract` DISABLE KEYS */;
INSERT INTO `contract` (`ID_C`,`CPassport`,`CFName`,`CLName`,`CMName`,`CSex`,`CBirthday`,`CAddress`,`CFDate`,`CLDate`) VALUES 
 (1,'4511134576','Dmitrij','Berdyaev','Ivanovich','m','1965-11-04','ulica Admirala Kruzenshterna dom 34','2000-01-11',NULL),
 (2,'4511452565','Anatolij','SHostakovich','Vasil\'evich','m','1945-03-10','prospekt Kutuzova dom 67','2001-03-13','2011-04-14'),
 (3,'4516324531','Mihajl','Konovalov','Dmitrievich','m','1967-12-26','prospekt Lenina dom 24','2007-09-01',NULL),
 (4,'3512345366','Aram','Babadzhanyan','Akopovich','m','1972-07-23','ulica akademika Minkovskogo dom 12','2006-12-06',NULL),
 (5,'4511223348','Anastasiya','Petrova','Andreevna','f','1987-03-01','ulica imeni SHostakovicha dom 56','2014-10-17',NULL),
 (6,'4511457387','David','Antonyan','Arutyunovich','m','1973-06-11','ulica generala Kuznecova dom 15','2005-05-25',NULL),
 (7,'2476677431','Mihail','Bershtejn','Aleksandrovich','m','1985-09-19','prospekt Stalina dom 71','2008-03-27','2012-05-12'),
 (8,'4511459998','Aleksandr','Ivanov','Dmitrievich','m','1985-12-13','ulica gineralissimusa Suvorova dom 93','2005-05-16','2009-01-19'),
 (9,'4513564432','Vladislav','Zotkin','Valer\'evich','m','1965-05-14','prospekt Varshavskij dom 101','2003-10-10','2012-10-01'),
 (10,'2476943313','Samuil','Skachkov','YAkovlevich','m','1989-07-18','ulica marshala ZHukova dom 16','2017-03-19',NULL),
 (11,'3512233423','Valerij','CHajkovskij	','Maratovich','m','1976-09-11','prospekt Pushkina dom 34','2016-01-12','2017-09-05'),
 (12,'4511679401','Natal\'ya','Smirnova','Mihajlovna','f','1986-11-11','ulica imeni Baumana dom 55','2018-03-07',NULL);
/*!40000 ALTER TABLE `contract` ENABLE KEYS */;


--
-- Definition of table `expenditure`
--

DROP TABLE IF EXISTS `expenditure`;
CREATE TABLE `expenditure` (
  `ID_EP` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `EPName` varchar(128) NOT NULL,
  `EPCost` int(10) unsigned NOT NULL,
  `ID_LEP` int(10) unsigned NOT NULL,
  `ID_IV` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID_EP`),
  KEY `FK_expenditure_1` (`ID_LEP`),
  KEY `FK_expenditure_2` (`ID_IV`),
  CONSTRAINT `FK_expenditure_1` FOREIGN KEY (`ID_LEP`) REFERENCES `lexpenditure` (`ID_LEP`),
  CONSTRAINT `FK_expenditure_2` FOREIGN KEY (`ID_IV`) REFERENCES `invoice` (`ID_IV`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `expenditure`
--

/*!40000 ALTER TABLE `expenditure` DISABLE KEYS */;
INSERT INTO `expenditure` (`ID_EP`,`EPName`,`EPCost`,`ID_LEP`,`ID_IV`) VALUES 
 (1,'Wi-Fi router Tenda AC6 (AC1200)',1500,1,1),
 (2,'Kreplenie routera KD1319',1000,8,1),
 (3,'Wi-Fi router ASUS RT-AC750',2500,5,2),
 (4,'Kreplenie routera KD1500',900,10,2),
 (5,'Kreplenie routera KD1500',900,10,2),
 (6,'Wi-Fi router ASUS RT-AC1300G Plus',5000,3,3),
 (7,'Kreplenie routera KD1930',3000,15,3),
 (8,'WI-FI router TP-Link TL-WR841N V14.0',1700,2,6),
 (9,'Kreplenie routera KD1503',1100,13,6),
 (10,'Kreplenie routera KD1503',1100,13,6),
 (11,'Kreplenie routera KD1503',1100,13,6),
 (12,'Wi-FI router Keenetic Extra (KN-1710)',4000,4,7),
 (13,'Kreplenie routera KD1900',2500,14,7),
 (14,'Wi-Fi router Tenda AC6 (AC1200)',1500,1,8),
 (15,'Kreplenie routera KD1501',1000,11,8),
 (16,'Kreplenie routera KD1501',1000,11,8),
 (17,'Wi-Fi router ASUS RT-AC750',2500,5,9),
 (18,'Kreplenie routera KD1500',900,10,9),
 (19,'Kreplenie routera KD1500',900,10,9),
 (20,'Wi-Fi router Tenda nova MW6-2',10000,6,10),
 (21,'Kreplenie routera KD1930',3000,15,10),
 (22,'Wi-FI router Keenetic Extra (KN-1710)',4000,4,11),
 (23,'Kreplenie routera KD1503',1100,13,11),
 (24,'Kreplenie routera KD1503',1100,13,11),
 (25,'Wi-Fi router TP-Link Archer A7',7000,7,12),
 (26,'Kreplenie routera KD1502',1200,12,12),
 (27,'Kreplenie routera KD1502',1200,12,12);
/*!40000 ALTER TABLE `expenditure` ENABLE KEYS */;


--
-- Definition of table `installer`
--

DROP TABLE IF EXISTS `installer`;
CREATE TABLE `installer` (
  `ID_IS` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `IPassport` varchar(10) NOT NULL,
  `IFName` varchar(32) NOT NULL,
  `ILName` varchar(32) NOT NULL,
  `IMName` varchar(32) NOT NULL,
  `ISex` varchar(1) NOT NULL,
  `IBirthday` date NOT NULL,
  `IAddress` varchar(128) NOT NULL,
  `IFDate` date NOT NULL,
  PRIMARY KEY (`ID_IS`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `installer`
--

/*!40000 ALTER TABLE `installer` DISABLE KEYS */;
INSERT INTO `installer` (`ID_IS`,`IPassport`,`IFName`,`ILName`,`IMName`,`ISex`,`IBirthday`,`IAddress`,`IFDate`) VALUES 
 (1,'4511324550','Andrej','Smolov','Ivanovich','m','1986-04-11','prospekt Ciolkovskogo dom 3','2010-01-11'),
 (2,'4511673225','Mihail','Sychyov','Mihajlovich','m','1982-01-22','ulica marshala Nazarova dom 123','2006-12-12'),
 (3,'4511197646','Vasilij','Ivanov','Petrovich','m','1977-11-14','ulica imeni Hachaturyana dom 34','2000-09-15'),
 (4,'3516665712','Aleksandr','Smirnov','Olegovich','m','1979-03-09','prospekt Kutuzova dom 2','2001-09-01'),
 (5,'4598776840','Dmitrij','Sobolev','Artyomevich','m','1969-11-14','prospekt Pushkina dom 64','1998-05-13'),
 (6,'4511456675','Ivan','Turgenev','Evgen\'evich','m','1988-03-11','ulica Ciolkovskogo dom 17','2010-05-01');
/*!40000 ALTER TABLE `installer` ENABLE KEYS */;


--
-- Definition of table `invoice`
--

DROP TABLE IF EXISTS `invoice`;
CREATE TABLE `invoice` (
  `ID_IV` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `IList` varchar(256) NOT NULL,
  `IAllCost` int(10) unsigned NOT NULL,
  `IDate` date NOT NULL,
  `ID_C` int(10) unsigned NOT NULL,
  `ID_IS` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID_IV`),
  KEY `FK_Invoice_1` (`ID_C`),
  KEY `FK_Invoice_2` (`ID_IS`),
  CONSTRAINT `FK_Invoice_1` FOREIGN KEY (`ID_C`) REFERENCES `contract` (`ID_C`),
  CONSTRAINT `FK_Invoice_2` FOREIGN KEY (`ID_IS`) REFERENCES `installer` (`ID_IS`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `invoice`
--

/*!40000 ALTER TABLE `invoice` DISABLE KEYS */;
INSERT INTO `invoice` (`ID_IV`,`IList`,`IAllCost`,`IDate`,`ID_C`,`ID_IS`) VALUES 
 (1,'SHirokopolosnyj dostup v internet, Hosting ',14700,'2015-03-17',1,2),
 (2,'Besprovodnoj dostup v internet',7800,'2006-01-12',2,3),
 (3,'SHirokopolosnyj dostup v internet, Rezervirovanie dannyh',22500,'2017-05-23',3,1),
 (4,'Arenda vydelennyh i virtual\'nyh serverov',12000,'2017-03-19',4,1),
 (5,'Podderzhka virtual\'nogo pochtovgo servera',3900,'2017-03-15',5,3),
 (6,'SHirokopolosnyj dostup v internet',11700,'2017-04-01',6,1),
 (7,'SHirokopolosnyj dostup v internet',13200,'2010-10-11',7,5),
 (8,'Kommutiruemyj dostup v internet, Kolokaciya',15500,'2008-11-03',8,2),
 (9,'Besprovodnoj dostup v internet',8200,'2011-03-11',9,1),
 (10,'SHirokopolosnyj dostup v internet, Hosting, Kolokaciya',33200,'2017-04-11',10,4),
 (11,'Kommutiruemyj dostup v internet, Rezervirovanie dannyh',18000,'2017-04-23',11,4),
 (12,'Kommutiruemyj dostup v internet',13400,'2018-04-25',12,3);
/*!40000 ALTER TABLE `invoice` ENABLE KEYS */;


--
-- Definition of table `lexpenditure`
--

DROP TABLE IF EXISTS `lexpenditure`;
CREATE TABLE `lexpenditure` (
  `ID_LEP` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `LEPName` varchar(128) NOT NULL,
  `LEPCost` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID_LEP`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `lexpenditure`
--

/*!40000 ALTER TABLE `lexpenditure` DISABLE KEYS */;
INSERT INTO `lexpenditure` (`ID_LEP`,`LEPName`,`LEPCost`) VALUES 
 (1,'Wi-Fi router Tenda AC6 (AC1200)',1500),
 (2,'WI-FI router TP-Link TL-WR841N V14.0',1700),
 (3,'Wi-Fi router ASUS RT-AC1300G Plus',5000),
 (4,'Wi-FI router Keenetic Extra (KN-1710)',4000),
 (5,'Wi-Fi router ASUS RT-AC750',2500),
 (6,'Wi-Fi router Tenda nova MW6-2',10000),
 (7,'Wi-Fi router TP-Link Archer A7',7000),
 (8,'Kreplenie routera KD1319',1000),
 (9,'Kreplenie routera KD1320',1200),
 (10,'Kreplenie routera KD1500',900),
 (11,'Kreplenie routera KD1501',1000),
 (12,'Kreplenie routera KD1502',1200),
 (13,'Kreplenie routera KD1503',1100),
 (14,'Kreplenie routera KD1900',2500),
 (15,'Kreplenie routera KD1930',3000);
/*!40000 ALTER TABLE `lexpenditure` ENABLE KEYS */;


--
-- Definition of table `lservice`
--

DROP TABLE IF EXISTS `lservice`;
CREATE TABLE `lservice` (
  `ID_LSV` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `LSVName` varchar(128) NOT NULL,
  `LSVCost` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID_LSV`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `lservice`
--

/*!40000 ALTER TABLE `lservice` DISABLE KEYS */;
INSERT INTO `lservice` (`ID_LSV`,`LSVName`,`LSVCost`) VALUES 
 (1,'SHirokopolosnyj dostup v internet',6700),
 (2,'Kommutiruemyj dostup v internet',4000),
 (3,'Besprovodnoj dostup v internet',3500),
 (4,'Hosting',5500),
 (5,'Podderzhka virtual\'nogo pochtovogo servera',3900),
 (6,'Kolokaciya',8000),
 (7,'Arenda vydelennyh i virtual\'nyh serverov',12000),
 (8,'Rezervirovanie dannyh',7800);
/*!40000 ALTER TABLE `lservice` ENABLE KEYS */;


--
-- Definition of table `report`
--

DROP TABLE IF EXISTS `report`;
CREATE TABLE `report` (
  `R_ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `R_Year` varchar(4) NOT NULL,
  `R_Month` varchar(2) NOT NULL,
  `R_Name` varchar(128) NOT NULL,
  `R_Count` int(10) unsigned NOT NULL,
  `R_Sum` int(10) unsigned NOT NULL,
  PRIMARY KEY (`R_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `report`
--

/*!40000 ALTER TABLE `report` DISABLE KEYS */;
INSERT INTO `report` (`R_ID`,`R_Year`,`R_Month`,`R_Name`,`R_Count`,`R_Sum`) VALUES 
 (1,'2017','4','SHirokopolosnyj dostup v internet',2,13400),
 (2,'2017','4','Kommutiruemyj dostup v internet',1,4000),
 (3,'2017','4','Besprovodnoj dostup v internet',0,0),
 (4,'2017','4','Hosting',1,5500),
 (5,'2017','4','Podderzhka virtual\'nogo pochtovogo servera',0,0),
 (6,'2017','4','Kolokaciya',1,8000),
 (7,'2017','4','Arenda vydelennyh i virtual\'nyh serverov',0,0),
 (8,'2017','4','Rezervirovanie dannyh',1,7800),
 (9,'2017','5','SHirokopolosnyj dostup v internet',1,6700),
 (10,'2017','5','Kommutiruemyj dostup v internet',0,0),
 (11,'2017','5','Besprovodnoj dostup v internet',0,0),
 (12,'2017','5','Hosting',0,0),
 (13,'2017','5','Podderzhka virtual\'nogo pochtovogo servera',0,0),
 (14,'2017','5','Kolokaciya',0,0),
 (15,'2017','5','Arenda vydelennyh i virtual\'nyh serverov',0,0),
 (16,'2017','5','Rezervirovanie dannyh',1,7800);
/*!40000 ALTER TABLE `report` ENABLE KEYS */;


--
-- Definition of table `service`
--

DROP TABLE IF EXISTS `service`;
CREATE TABLE `service` (
  `ID_SV` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `SVName` varchar(128) NOT NULL,
  `SVCost` int(11) NOT NULL,
  `ID_LSV` int(10) unsigned NOT NULL,
  `ID_IV` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID_SV`) USING BTREE,
  KEY `FK_work_2` (`ID_IV`),
  KEY `FK_work_1` (`ID_LSV`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `service`
--

/*!40000 ALTER TABLE `service` DISABLE KEYS */;
INSERT INTO `service` (`ID_SV`,`SVName`,`SVCost`,`ID_LSV`,`ID_IV`) VALUES 
 (1,'SHirokopolosnyj dostup v internet',6700,1,1),
 (2,'Hosting',5500,4,1),
 (3,'Besprovodnoj dostup v internet',3500,3,2),
 (4,'SHirokopolosnyj dostup v internet',6700,1,3),
 (5,'Rezervirovanie dannyh',7800,8,3),
 (6,'Arenda vydelennyh i virtual\'nyh serverov',12000,7,4),
 (7,'Podderzhka virtual\'nogo pochtovgo servera',3900,5,5),
 (8,'SHirokopolosnyj dostup v internet',6700,1,6),
 (9,'SHirokopolosnyj dostup v internet',6700,1,7),
 (10,'Kommutiruemyj dostup v internet',4000,2,8),
 (11,'Kolokaciya',8000,6,8),
 (12,'Besprovodnoj dostup v internet',3500,3,9),
 (13,'SHirokopolosnyj dostup v internet',6700,1,10),
 (14,'Hosting',5500,4,10),
 (15,'Kolokaciya',8000,6,10),
 (16,'Kommutiruemyj dostup v internet',4000,2,11),
 (17,'Rezervirovanie dannyh',7800,8,11),
 (18,'Kommutiruemyj dostup v internet',4000,2,12);
/*!40000 ALTER TABLE `service` ENABLE KEYS */;


--
-- Definition of procedure `Add_report`
--

DROP PROCEDURE IF EXISTS `Add_report`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='' */ $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `Add_report`(TYear CHAR(4), TMonth CHAR(2))
BEGIN
        DECLARE TID INTEGER;
        DECLARE TName CHAR(128);
        DECLARE TCount INTEGER;
        DECLARE TSum INTEGER;

        DECLARE Control INTEGER;
        DECLARE Done INTEGER DEFAULT 0;
        DECLARE Rep CURSOR FOR
                SELECT ID_LSV, LSVName, COUNT(SVName), SUM(SVCost)
                FROM `internet_provider`.`lservice` LEFT JOIN (
                     SELECT ID_LSV, SVName, SVCost
                     FROM `internet_provider`.`service`
                     JOIN `internet_provider`.`invoice` USING(ID_IV)
                     WHERE YEAR(IDate) = TYear AND MONTH(IDate) = TMonth)
                     Temp
                USING(ID_LSV)
                GROUP BY ID_LSV;
        DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET Done = 1;

       	OPEN Rep;
        REPEAT
        	FETCH Rep INTO TID, TName, TCount, TSum;
                IF TSum IS NULL THEN
                	SET TSum = 0;
                END IF;

                IF Done = 0 THEN
                	INSERT INTO `internet_provider`.`report`
                        VALUES(NULL, TYear, TMonth, TName, TCount, TSum);
                END IF;
        UNTIL Done = 1
       	END REPEAT;

        CLOSE Rep;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
