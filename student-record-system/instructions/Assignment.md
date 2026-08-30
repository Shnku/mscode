Assignment 1 | AI/ML Laboratory | M.Sc. 1st Semester

# Problem Statement: Student Record Management System

Develop a simple Student Record Management System using Python. The system should maintain student information and store and retrieve it using different file formats.

Each student should have at least the following information:

* Student ID
* Name
* Department
* Semester
* Marks in three subjects

You should create a Student class to represent a student.

The program should allow the user to:

1. Add a new student
2. Display student information
3. Calculate the student's total marks
4. Calculate the student's average marks
5. Determine whether the student has passed or failed
6. Search for a student using Student ID
7. Save student information to files
8. Read previously saved information from files

# Part A Working with Text Files

Create a text file containing student information. For example:

``` text
101, Rahul, Computer Science, 1, 78, 82, 69
102, Priya, Computer Science, 1, 91, 87, 94 
103, Amit, Mathematics, 1, 65, 71, 68

```

*(Note: Data derived from source text records).*

Your program should:

* Read the file
* Convert each record into a Student object
* Display the student information
* Calculate total and average marks using methods of the Student class

### You should practice

* `open()`
* `read()`
* `readline()`
* `readlines()`
* `write()`
* `with open(...)`
* Different file modes such as `r`, `w`, and `a`

# Part B Working with CSV Files

Store the student records in a CSV file. The CSV file should contain a header such as: `Student_ID, Name, Department, Semester, Subject1, Subject2, Subject3`.

Your program should:

* Read the CSV file
* Create Student objects from the records
* Display the students
* Add a new student
* Save the updated records to another CSV file

### You should practice

* Python's `csv` module
* `csv.reader`
* `csv.writer`
* Reading rows
* Writing rows
* Handling a header row

**Do not use Pandas for this part.**

# Part C Working with JSON Files

Store student information in a JSON file. A record may look like:

``` json
{
  "student id": 101,
  "name": "Rahul",
  "department": "Computer Science",
  "semester": 1,
  "marks": {
    "subject1": 78,
    "subject2": 82,
    "subject3": 69
  }
}

```

*(Note: Structure derived from formatting pieces in the source text).*

Your program should:

* Read student information from JSON
* Create Student objects
* Display the information
* Modify a student's marks
* Save the updated information into a JSON file

### You should practice

* `json.load()`
* `json.dump()`
* Dictionaries and lists
* Converting file data into Python objects

# Part D Object-Oriented Programming

Your `Student` class should contain appropriate attributes and methods.

For example, your class should have methods that perform operations such as:

* `calculate_total()`
* `calculate_average()`
* `get_result()`
* `display_student()`

You should also implement at least one method that modifies student information, such as: `update_marks()`.

### Additional OOP requirement

Create a separate class called `StudentManager`. Its responsibility should be to manage multiple `Student` objects. It should provide methods such as:

* `add_student()`
* `remove_student()`
* `search_student()`
* `display_all_students()`
* `save_to_file()`
* `load_from_file()`

You do not need to implement complicated inheritance or advanced OOP. The purpose is to understand the difference between an object representing one student and a class managing multiple student objects.

# Suggested Program/Class Structure

A possible structure is:

### Student

* attributes
* `calculate_total()`
* `calculate_average()`
* `get_result()`
* `update_marks()`
* `display_student()`

### StudentManager

* `add_student()`
* `search_student()`
* `remove_student()`
* `display_all_students()`
* `load_from_file()`
* `save_to_file()`

This is a suggested class structure, not a complete solution.
