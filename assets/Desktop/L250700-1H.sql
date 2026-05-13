USE NUCES;
GO
DROP TABLE Attendance;
DROP TABLE Student;
DROP TABLE ClassVenue;
DROP TABLE Teacher;
GO

CREATE TABLE Student (
    RollNum VARCHAR(10) NOT NULL PRIMARY KEY,
    StudentName VARCHAR(20),
    Gender VARCHAR(10),
    Phone VARCHAR(15)
);
GO

INSERT INTO Student VALUES
('L230844', 'Ahmed Muaz', 'Male', '0389765432'),
('L124147', 'Kalsoom', 'Female', '03983455678'),
('L230954', 'Sabih ud Din', 'Male', '03453243567');
GO

SELECT * FROM Student;
GO

CREATE TABLE Attendance (
    RollNum VARCHAR(20) NOT NULL,
    AttendanceDate DATE NOT NULL,
    Status VARCHAR(5),
    ClassVenue INT,
    CONSTRAINT pk_attendance PRIMARY KEY (RollNum, AttendanceDate)
);
GO

INSERT INTO Attendance VALUES
('L230844', '2016-02-22', 'P', 2),
('L124147', '2016-02-23', 'A', 1),
('L230654', '2016-03-04', 'P', 2);
GO

SELECT * FROM Attendance;
GO

CREATE TABLE ClassVenue (
    ID INT NOT NULL PRIMARY KEY,
    Building VARCHAR(50),
    RoomNum INT,
    TeacherId INT
);
GO

INSERT INTO ClassVenue VALUES
(1, 'CS', 2, 1),
(2, 'Civil', 7, 2);
GO

SELECT * FROM ClassVenue;
GO

CREATE TABLE Teacher (
    ID INT NOT NULL PRIMARY KEY,
    TeacherName VARCHAR(50),
    Designation VARCHAR(50),
    Department VARCHAR(50)
);
GO

INSERT INTO Teacher VALUES
(1, 'Dr. Zeeshan Ali Rana', 'Assistant Prof.', 'Software Engineering'),
(2, 'Mr. Zeeshan Nazar', 'Lecturer', 'Data Science'),
(3, 'Mamoona Majid', 'Lecturer', 'Computer Science');
GO

SELECT * FROM Teacher;
GO

SELECT --Join all rows
    S.RollNum,
    S.StudentName,
    S.Gender,
    S.Phone,
    A.AttendanceDate,
    A.Status,
    CV.Building,
    CV.RoomNum,
    T.TeacherName,
    T.Designation,
    T.Department
FROM 
    Attendance A
INNER JOIN 
    Student S ON A.RollNum = S.RollNum
LEFT JOIN 
    ClassVenue CV ON A.ClassVenue = CV.ID
LEFT JOIN 
    Teacher T ON CV.TeacherId = T.ID;
GO

INSERT INTO Student
VALUES
('L162334', 'Fozan Shahid', 'Male', '0321456789');
GO

INSERT INTO ClassVenue
VALUES
(3, 'CS', 5, 7);
GO

SELECT * FROM ClassVenue;
GO

UPDATE Teacher
SET TeacherName = 'Ms. Mamoona Majid'
WHERE TeacherName LIKE 'mamoona majid';

UPDATE Teacher
SET TeacherName = 'Ms. Mamoona Majid'
WHERE ID = 3;
GO

SELECT * FROM Student;
GO

DELETE FROM Student
WHERE RollNum = 'L230844';  --Deleted

GO

SELECT * FROM Attendance;
GO

DELETE FROM Attendance
WHERE RollNum = 'L129083' AND Status LIKE 'A';
GO

-- Queries 

SELECT StudentName, Gender, RollNum
FROM Student
WHERE Gender = 'Male' 
  AND Phone LIKE '03%';
GO

SELECT ID, TeacherName 
FROM Teacher
WHERE Department LIKE 'Computer Science' 
   OR Designation LIKE 'Professor';
GO


SELECT * FROM Student
WHERE Gender = 'Male';
;
GO

SELECT * FROM Teacher
WHERE Designation LIKE 'Assistant Prof%' 
  AND Department NOT LIKE 'Math%';
GO

SELECT * FROM Student

WHERE 
   RollNum >'%1000' AND "StudentName" LIKE 'A%';