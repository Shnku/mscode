from csv_handler import *
from file_handler import *
from json_handler import *
from student import Student


# Student Manager class..
class StudentManager:
    def __init__(self):
        self.student: list[Student] = []

    def add_student(self, sid: int, name: str, dept: str, sem: str, marks: list):
        self.student.append(Student(sid, name, dept, sem, marks))

    def remove_student(self, sid: int):
        for i in self.student:
            if i.sid == sid:
                self.student.remove(i)
                print(f"Student removed {i.name}")
                return self.student
        print("Student not found")

    def search_student(self, sid):
        for i in self.student:
            if i.sid == sid:
                return i
        print("Student not found")

    def display_all_student(self, only_data=True):
        out_str = f"{'SID':<3} {'Name':<10} {'Dept':<8} {'Sem':<4} {'Marks':<10}"
        if not only_data:
            print(f"\n--- All Student Records ( {len(self.student)}) ---")
            out_str = out_str + f" {'Total':<7} {'Average':<7} {'Result':<7}"
        print(out_str)
        print("-" * 100)
        for i in self.student:
            print(i.display_student_row(only_data))
        print("-" * 100)

    def save_to_file(self, filename, format):
        if format == "csv":
            write_csv_file(filename, self.student)
        elif format == "json":
            write_json_file(filename, self.student)
        elif format == "txt":
            write_txt_file(filename, self.student)
        else:
            print("Invalid format")
            return False
        return True

    def load_from_file(self, filename, format):
        if format == "csv":
            data = read_csv_file(filename)
            for i in data:
                self.student.append(convert_csv_to_student_object(i))
        elif format == "json":
            data = read_json_file(filename)
            for i in data:
                self.student.append(convert_json_to_student_object(i))
        elif format == "txt":
            data = read_from_file(filename)
            self.student.extend(data)
        else:
            print("Invalid format")
            return False
        return True


# individually test this class file only...
if __name__ == "__main__":
    manager = StudentManager()
    print("\nAdding students...")
    manager.add_student(101, "Rahul", "CSE", "1st", [39, 80, 85])
    manager.add_student(102, "Priya", "ECE", "1st", [49, 80, 91])
    manager.add_student(103, "Amit", "CSE", "1st", [29, 80, 78])
    manager.display_all_student()

    manager.search_student(102)

    manager.save_to_file("./data/test_students.csv", "csv")
    manager.save_to_file("./data/test_students.json", "json")
    manager.save_to_file("./data/test_students.txt", "txt")

    manager.remove_student(102)
    manager.display_all_student()
