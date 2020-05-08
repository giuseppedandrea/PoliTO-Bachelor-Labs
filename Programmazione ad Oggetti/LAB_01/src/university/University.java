package university;

public class University {
	// Constants
	private static final int MAX_STUDENT = 1000;
	private static final int MAX_COURSE = 50;
	private static final int ID_START = 10000;
	private static final int CODE_START = 10;
	
	// Attributes
	private String universityName;
	private String rectorFirstname;
	private String rectorLastname;
	private Student[] student;
	private Course[] course;
	
	// Variables
	private int nextId = ID_START;
	private int nextCode = CODE_START;

	/**
	 * Constructor
	 * @param name name of the university
	 */
	public University(String name){
		universityName = name;
		student = new Student[MAX_STUDENT];
		course = new Course[MAX_COURSE];
	}
	
	/**
	 * Getter for the name of the university
	 * @return name of university
	 */
	public String getName(){
		return universityName;
	}
	
	/**
	 * Defines the rector for the university
	 * @param first
	 * @param last
	 */
	public void setRector(String first, String last){
		rectorFirstname = first;
		rectorLastname = last;
	}
	
	/**
	 * Retrieves the rector of the university
	 * @return
	 */
	public String getRector(){
		return (rectorFirstname + " " + rectorLastname);
	}
	
	/**
	 * Enroll a student in the university
	 * @param first first name of the student
	 * @param last last name of the student
	 * @return
	 */
	public int enroll(String first, String last){
		student[nextId-ID_START] = new Student(first, last, nextId);
		return nextId++;
	}
	
	/**
	 * Retrieves the information for a given student
	 * @param id the id of the student
	 * @return information about the student
	 */
	public String student(int id){
		return student[id-ID_START].toString();
	}
	
	/**
	 * Activates a new course with the given teacher
	 * @param title title of the course
	 * @param teacher name of the teacher
	 * @return the unique code assigned to the course
	 */
	public int activate(String title, String teacher){
		course[nextCode-CODE_START] = new Course(title, teacher, nextCode);
		return nextCode++;
	}
	
	/**
	 * Retrieve the information for a given course
	 * @param code unique code of the course
	 * @return information about the course
	 */
	public String course(int code){
		return course[code-CODE_START].toString();
	}
	
	/**
	 * Register a student to attend a course
	 * @param studentID id of the student
	 * @param courseCode id of the course
	 */
	public void register(int studentID, int courseCode){
		student[studentID-ID_START].addCourseToStudent(course[courseCode-CODE_START]);
		course[courseCode-CODE_START].addStudentToCourse(student[studentID-ID_START]);
	}
	
	/**
	 * Retrieve a list of attendees
	 * @param courseCode unique id of the course
	 * @return list of attendees separated by "\n"
	 */
	public String listAttendees(int courseCode){
		return course[courseCode-CODE_START].listCourseStudents();
	}

	/**
	 * Retrieves the study plan for a student
	 * @param studentID id of the student
	 * @return list of courses the student is registered for
	 */
	public String studyPlan(int studentID){
		return student[studentID-ID_START].listStudentCourses();
	}
}
