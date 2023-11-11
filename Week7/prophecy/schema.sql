/* RENAME TABLE CORRECT ORDER
    1- Create new table
    2- Copy data
    3- Drop old table
    4- Rename new into old
*/
BEGIN TRANSACTION;

CREATE TABLE students_t (
    id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

INSERT INTO students_t (student_name)
        SELECT student_name
        from students
        ORDER BY student_name ASC;

ALTER TABLE students RENAME TO students_copy;
ALTER TABLE students_t RENAME TO students;


CREATE TABLE houses (
    id INTEGER NOT NULL,
    house_name TEXT NOT NULL,
    house_head TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE assignments (
    id INTEGER PRIMARY KEY,
    house_id INTEGER,
    students_id INTEGER,
    FOREIGN KEY(house_id) REFERENCES houses(id)
    FOREIGN KEY(students_id) REFERENCES students(id)
);
COMMIT;
