# handling CSV..
import csv

from student import Student


def read_csv_file(filepath):
    with open(filepath, mode="r") as file:
        csv_data = list(csv.reader(file))
        # for row in csv_data:
        #     print(row)
        return csv_data[1:]


def convert_csv_to_student_object(data):
    return Student(
        sid=int(data[0]),
        name=data[1],
        dept=data[2],
        sem=data[3],
        marks=[int(x) for x in data[4:]],
    )


def write_csv_file(filepath, student_data):
    with open(filepath, mode="w") as f:
        writr = csv.writer(f)
        writr.writerow(
            [
                "Student_ID",
                "Name",
                "Department",
                "Semester",
                "Subject1",
                "Subject2",
                "Subject3",
            ]
        )
        for student in student_data:
            writr.writerow(
                [
                    student.sid,
                    student.name,
                    student.dept,
                    student.sem,
                    student.marks[0],
                    student.marks[1],
                    student.marks[2],
                ]
            )


# test this file only...
if __name__ == "__main__":
    list_data = read_csv_file("./data/students.csv")
    for i in list_data:
        print(i)
