# For handelling Json..
import json

from student import Student


def read_json_file(filepath):
    json_data = None
    with open(filepath, "r") as file:
        json_data = json.load(file)
        # print(json_data)
    return json_data


def convert_json_to_student_object(data):
    marks = [
        data["marks"]["subject1"],
        data["marks"]["subject2"],
        data["marks"]["subject3"],
    ]
    return Student(data["sid"], data["name"], data["dept"], data["sem"], marks)


def write_json_file(filepath, students):
    data = [
        {
            "sid": student.sid,
            "name": student.name,
            "dept": student.dept,
            "sem": student.sem,
            "marks": {
                "subject1": student.marks[0],
                "subject2": student.marks[1],
                "subject3": student.marks[2],
            },
        }
        for student in students
    ]
    with open(filepath, "w") as file:
        json.dump(data, file, indent=4)


# test this file individually..
if __name__ == "__main__":
    print(read_json_file("./data/students.json"))
