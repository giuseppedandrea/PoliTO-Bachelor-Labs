package university;

public class Student {
	// Constants
	private static final int MAX_STUDENT_COURSES = 25;
	
	// Attributes
	private String studentFirstname;
	private String studentLastname;
	private int studentID;
	private Course[] studentCourses;
	
	// Variables
	private int nextStudentCourse = 0;
	
	public Student(String first, String last, int id) {
		studentFirstname = first;
		studentLastname = last;
		studentID = id;
		studentCourses = new Course[MAX_STUDENT_COURSES];
	}

	public String getStudentFirstname() {
		return studentFirstname;
	}

	public String getStudentLastname() {
		return studentLastname;
	}

	public int getId() {
		return studentID;
	}
	
	public String toString() {
		return getId() + " " + getStudentFirstname() + " " + getStudentLastname();
	}
	
	public void addCourseToStudent(Course course) {
		studentCourses[nextStudentCourse++] = course;
	}
	
	public String listStudentCourses() {
		StringBuffer result = new StringBuffer("");
		for (Course course : studentCourses) {
			if (course != null) {
				result.append(course.toString()).append("\n");
			}
		}
		return result.toString();
	}
}
