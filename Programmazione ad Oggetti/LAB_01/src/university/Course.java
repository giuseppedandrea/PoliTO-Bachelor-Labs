package university;

public class Course {
	// Constants	
	private static final int MAX_COURSE_STUDENTS = 100;
	
	// Attributes
	private String courseTitle;
	private String teacherName;
	private int courseCode;
	private Student[] courseStudents;
	
	// Variables
	private int nextcourseStudents = 0;
	
	public Course(String title, String teacher, int code) {
		courseTitle = title;
		teacherName = teacher;
		courseCode = code;
		courseStudents = new Student[MAX_COURSE_STUDENTS];
	}

	public String getCourseTitle() {
		return courseTitle;
	}

	public String getTeacherName() {
		return teacherName;
	}

	public int getCourseCode() {
		return courseCode;
	}
	
	public String toString() {
		return getCourseCode() + " " + getCourseTitle() + "" + getTeacherName();
	}

	public void addStudentToCourse(Student student) {
		courseStudents[nextcourseStudents++] = student;
	}
	
	public String listCourseStudents() {
		StringBuffer result = new StringBuffer("");
		for (Student student : courseStudents) {
			if (student != null) {
				result.append(student.toString()).append("\n");
			}
		}
		return result.toString();
	}
}
