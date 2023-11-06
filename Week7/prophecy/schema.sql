## RENAME TABLE CORRECT ORDER

    Create new table
    Copy data
    Drop old table
    Rename new into old 


CREATE TABLE students_t (
    id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

INSERT INTO students_t (student_name)
        SELECT student_name 
        from students
        ORDER BY student_name ASC;



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
    FOREING KEY(house_id) REFERENCES houses(id)
    FOREING KEY(students_id) REFERENCES students(id)
);
