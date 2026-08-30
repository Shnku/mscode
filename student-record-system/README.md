# Student Record Management System (SRMS)

## A. Title

**Student Record Management System (SRMS)**

## B. Objective

The objective of this assignment is to develop a command-line application in Python that demonstrates core concepts of Object-Oriented Programming (OOP) and file handling. The system maintains student academic profiles, performs computations on their grades, and stores/retrieves information using different file formats (plain TXT, structured CSV, and nested JSON).

## C. Features

* **Student Entity Creation**: Models students with details including ID, Name, Department, Semester, and individual marks in three subjects.
* **Database Operations (CRUD)**:
  * Add a new student record dynamically with duplicate ID check validation.
  * Display detailed profile listings of all loaded students.
  * Search for a student record by ID.
  * Delete a student record by ID.
* **Academic Calculation**: Computes total marks, average marks, and final results (Pass/Fail) based on individual subject pass limits.
* **Multi-Format Storage Engines**:
  * **TXT**: Plain-text line parsing and serialization (assuming in comma seperated format).
  * **CSV**: Header-safe tabular data operations using Python's built-in `csv` module.
  * **JSON**: Nested structure parsing and serializing using Python's built-in `json` module, with robust key-mapping fallback handling.

## D. Project Structure

The program is split across the following files:

```text
.
├── data
│   ├── students.csv
│   ├── students.json
│   └── students.txt
├── file_handler.py       -- handling text files
├── csv_handler.py        -- handling csv files
├── json_handler.py       -- handling json files
├── main.py               -- main function to run the program (entry point)
├── manager.py            -- manager class to manage student records
├── student.py            -- student class to create student objects
└── README.md
```

## E. Requirements

* **Python**: Version `3.10` or higher (required for `match-case` statements in the CLI).
* **Dependencies**: None. The system relies entirely on standard library modules (`argparse`, `os`, `csv`, `json`).

## F. How to Run

Run the program from the command line by providing the database file path and its format.

### Run with Text file

```bash
python main.py --file data/students.txt --format txt
```

### Run with CSV file

```bash
python main.py --file data/students.csv --format csv
```

### Run with JSON file

```bash
python main.py --file data/students.json --format json
```

## G. Input and Output

* **Inputs**:
  * Command-line arguments (`--file` and `--format`).
  * Text inputs during the interactive CLI menu loop (IDs, Names, Marks).
  * Data files structured as comma-separated values (TXT/CSV) or JSON array structures.
* **Outputs**:
  * Terminal text interfaces displaying student profile cards, menus, and feedback alerts.
  * Formatted output data files saved to the path specified in the startup arguments.

### Sample Row Formats

* **TXT Row**: `101, Rahul, Computer Science, 1, 78, 82, 69`
* **CSV Row**: `101,Rahul,CSE,1st,39,80,85`
* **JSON Object**:

```json
{
    "sid": 101,
    "name": "Rahul",
    "dept": "Math",
    "sem": "1st",
    "marks": {
        "subject1": 78,
        "subject2": 82,
        "subject3": 69
    }
}
```

## H. OOP Concepts Used

* **Classes**: Used `Student` to model a single record and `StudentManager` to manage the collection of records.
* **Objects**: Instances of `Student` are initialized dynamically from loaded file entries and user prompts.
* **Constructors**: Defined `__init__` in both classes to set up starting fields and initialize lists.
* **Instance Methods**:
  * `calculate_total()` and `calculate_average()` process grade averages.
  * `get_result()` determines pass/fail thresholds (passing require $\ge 33$ in every subject).
  * `display_student()` prints formatted terminal outputs.
  * `add_student()`, `remove_student()`, and `search_student()` manage memory state.

## I. File Handling Concepts Used

* **Context Managers (`with open(...)`)**: Ensures file streams are safely opened and closed without resource leaks.
* **CSV Parser (`csv.reader` & `csv.writer`)**: Reads and writes tabular data without relying on external libraries like Pandas.
* **JSON Serializer (`json.load` & `json.dump`)**: Loads structured tree data and writes formatted JSON using `indent=4`.
* **String Processing (`strip()`, `split()`, `map()`)**: Sanitizes spaces and splits text fields on commas when parsing raw `.txt` configurations.

## J. Sample Output

```text
$ python main.py --file ./data/students.csv --format csv
Loading records from ./data/students.csv...
Loaded 3 student(s).

=== Student Record Management System ===
1. Add a New Student
2. Display All Students
3. Search for a Student by ID
4. Remove a Student by ID
5. Calculate Total & Average Marks
6. Save Records to File
7. Display All Students including their Results
8. Exit
Enter choice (1-8): 7
Print All details of Students........

--- All Student Records ( 3) ---
SID Name       Dept     Sem  Marks      Total   Average Result 
----------------------------------------------------------------------------------------------------
101 Rahul      CSE      1st  39,80,85   204.00  68.00   Pass   
102 Priya      ECE      1st  49,80,91   220.00  73.33   Pass   
103 Amit       CSE      1st  29,80,78   187.00  62.33   Fail   
----------------------------------------------------------------------------------------------------

=== Student Record Management System ===
1. Add a New Student
2. Display All Students
3. Search for a Student by ID
4. Remove a Student by ID
5. Calculate Total & Average Marks
6. Save Records to File
7. Display All Students including their Results
8. Exit
Enter choice (1-8): 6
Saving records to file data/students.csv.........
Saved 3 student(s) to data/students.csv successfully.

=== Student Record Management System ===
1. Add a New Student
2. Display All Students
3. Search for a Student by ID
4. Remove a Student by ID
5. Calculate Total & Average Marks
6. Save Records to File
7. Display All Students including their Results
8. Exit
Enter choice (1-8): 8
Exiting program!.........
Exit code: 0
```

## K. Learning Outcome / Conclusion

Through this project, I gained practical experience in structuring modular, multi-file Python applications. I learned how to separate the application's domain model (the `Student` and `StudentManager` classes) from its presentation layer (`main.py`) and data persistence handlers. I also gained insights into managing structural compatibility, parsing files robustly to prevent runtime exceptions, and utilizing Python's built-in parsing modules effectively.
