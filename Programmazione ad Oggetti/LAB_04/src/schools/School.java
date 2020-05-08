package schools;

import java.util.Collection;
import java.util.LinkedList;

/**
 * Represents the schools.
 * Schools are aggregations of branches, 
 * each school has one or more {@link Branch branches} (at least one)
 *
 */
public class School {
	

	private String name;
	private String code;
	private int grade;
	private String description;
	private Collection<Branch> branchs = new LinkedList<Branch>();

	public School(String name, String code, int grade, String description) {
		this.name = name;
		this.code = code;
		this.grade = grade;
		this.description = description;
	}

	/**
	 * Getter method for the school name
	 * @return name of the school
	 */
	public String getName() {
		return name;
	}

	/**
	 * Getter method for the school code
	 * @return code of the school
	 */
	public String getCode() {
		return code;
	}

	/**
	 * Getter method for the grade
	 * @return grade
	 */
	public int getGrade() {
		return grade;
	}

	/**
	 * Getter method for the description
	 * @return description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Retrieves the branches of the school.
	 * 
	 * @return collection of the branches
	 */
	public Collection<Branch> getBranches() {
		return branchs;
	}
	
	void addBranch(Branch branch) {
		branchs.add(branch);
	}

}
