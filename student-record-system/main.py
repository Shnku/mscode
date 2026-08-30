import argparse
import os

from manager import StudentManager


def main():
    parser = argparse.ArgumentParser(description="Student Record Management System")
    parser.add_argument("--file", required=True, help="input file path")
    parser.add_argument(
        "--format", required=True, choices=["txt", "csv", "json"], help="file format"
    )
    args = parser.parse_args()

    manager = StudentManager()

    if os.path.exists(args.file):
        print(f"Loading records from {args.file}...")
        manager.load_from_file(args.file, args.format)
        print(f"Loaded {len(manager.student)} student(s).")
    else:
        print(
            f"File '{args.file}' not found. Starting with an empty student records database."
        )

    while True:
        print("\n=== Student Record Management System ===")
        print("1. Add a New Student")
        print("2. Display All Students")
        print("3. Search for a Student by ID")
        print("4. Remove a Student by ID")
        print("5. Calculate Total & Average Marks")
        print("6. Save Records to File")
        print("7. Display All Students including their Results")
        print("8. Exit")

        choice = input("Enter choice (1-8): ").strip()

        match choice:
            case "1":
                try:
                    sid = int(input("Enter Student ID (integer): ").strip())
                    if any(s.sid == sid for s in manager.student):
                        print("Error: Student with this ID already exists.")
                        continue
                    name = input("Enter Student Name: ").strip()
                    dept = input("Enter Department: ").strip()
                    sem = input("Enter Semester: ").strip()
                    marks = []
                    for i in range(3):
                        mark = int(input(f"Enter Marks for Subject{i + 1}: ").strip())
                        marks.append(mark)
                    manager.add_student(sid, name, dept, sem, marks)
                    print(f"Student '{name}' added successfully.")
                except ValueError:
                    print("Invalid input. Please enter numbers for ID and marks.")

            case "2":
                if not manager.student:
                    print("No student records available.")
                else:
                    manager.display_all_student()

            case "3":
                try:
                    sid = int(input("Enter Student ID to search: ").strip())
                    student = manager.search_student(sid)
                    if student:
                        print("\n--- Student Found ---")
                        student.display_student_details()
                except ValueError:
                    print("Invalid input. Student ID must be an integer.")

            case "4":
                try:
                    sid = int(input("Enter Student ID to remove: ").strip())
                    manager.remove_student(sid)
                except ValueError:
                    print("Invalid input. Student ID must be an integer.")

            case "5":
                try:
                    sid = int(input("Enter Student ID to calculate marks: ").strip())
                    student = manager.search_student(sid)
                    if student:
                        student.display_student_details()
                except ValueError:
                    print("Invalid input. Student ID must be an integer.")

            case "6":
                print(f"Saving records to {args.file} in {args.format} format...")
                manager.save_to_file(args.file, args.format)
                print("Records saved successfully.")

            case "7":
                print("Print All details of Students........")
                manager.display_all_student(only_data=False)
            case "8":
                print("Exiting program!.........")
                break
            case _:
                print("Invalid choice. Please enter a number between 1 and 7.")


if __name__ == "__main__":
    main()
