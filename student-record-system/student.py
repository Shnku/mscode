# Student class.......
class Student:
    def __init__(self, sid: int, name: str, dept: str, sem: str, marks: list):
        self.sid = sid
        self.name = name
        self.dept = dept
        self.sem = sem
        self.marks = marks

    def calculate_total(self):
        return sum(self.marks)

    def calculate_average(self):
        return sum(self.marks) / len(self.marks)

    def update_marks(self, marks):
        self.marks = marks

    def update_name(self, name):
        self.name = name

    def update_semester(self, sem):
        self.sem = sem

    def get_result(self):
        for i in self.marks:
            if i < 33:
                return "Fail"
        return "Pass"

    def display_student_details(self):
        print(f"Student ID: {self.sid}, Name: {self.name}, Department: {self.dept}")
        print(f"Semester: {self.sem}")
        print(f"Marks: {self.marks}")
        print(f"Total: {self.calculate_total()}")
        print(f"Average: {self.calculate_average()}")
        print(f"Result: {self.get_result()}")

    def display_student_row(self, only_data=True):
        marks_str = ",".join(map(str, self.marks))
        out_str = f"{self.sid:<3} {self.name:<10} {self.dept:<8} {self.sem:<4} {marks_str:<10}"
        if not only_data:
            total = self.calculate_total()
            average = self.calculate_average()
            result = self.get_result()
            return f"{out_str} {total:<7.2f} {average:<7.2f} {result:<7}"
        else:
            return out_str


# test this class file only...
if __name__ == "__main__":
    student1 = Student(1, "John", "CSE", "1st", [80, 70, 60])
    print(student1.display_student_row())
    student2 = Student(2, "Priya", "ECE", "1st", [80, 70, 60])
    print(student2.display_student_row())
    student1.display_student_details()
