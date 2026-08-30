from student import Student


def read_from_file(filepath):
    """Assuming in comma seperated format"""
    data = []
    with open(filepath) as file:
        while True:
            line = file.readline()
            if not line:
                break
            line = line.strip().split(",")
            data.append(
                Student(
                    int(line[0]), line[1], line[2], line[3], [int(x) for x in line[4:]]
                )
            )
    return data


def write_txt_file(filepath, students):
    """Just put the console print out things as rowise format into file
    So, this is not compatible with `read_from_file()` method
    """
    with open(filepath, "w") as file:
        for student in students:
            file.writelines(student.display_student_row() + "\n")


# test this file only.......
if __name__ == "__main__":
    print("Testing write_txt_file:")
    test_students = read_from_file("./data/students.txt")
    # write_txt_file("./data/test_students2.txt", test_students)
    for s in test_students:
        print(s)
