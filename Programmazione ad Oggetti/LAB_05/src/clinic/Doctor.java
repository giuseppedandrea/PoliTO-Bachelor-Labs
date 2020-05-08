package clinic;

import java.util.Collection;
import java.util.LinkedList;

public class Doctor extends Patient {
	
	private int docID;
	private String specialization;
	private Collection<Patient> patients = new LinkedList<>();

	public Doctor(String first, String last, String ssn, int docID, String specialization) {
		super(first, last, ssn);
		this.docID = docID;
		this.specialization = specialization;
	}

	public int getDocID() {
		return docID;
	}

	public String getSpecialization() {
		return specialization;
	}
	
	public Collection<Patient> getPatients() {
		return patients;
	}
	
	public String toString() {
		return super.toString() + " [" + getDocID() + "]: " + getSpecialization();
	}
	
	public void addPatientToDoctor(Patient patient) {
		patients.add(patient);
	}

}
