package clinic;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import static java.util.stream.Collectors.*;
import static java.util.Comparator.*;

/**
 * Represents a clinic with patients and doctors.
 * 
 */
public class Clinic {
	
	private Map<String, Patient> patients = new HashMap<>();
	private Map<Integer, Doctor> doctors = new HashMap<>();

	/**
	 * Add a new clinic patient.
	 * 
	 * @param first first name of the patient
	 * @param last last name of the patient
	 * @param ssn SSN number of the patient
	 */
	public void addPatient(String first, String last, String ssn) {
		Patient patient = new Patient(first, last, ssn);
		patients.put(ssn, patient);
	}

	/**
	 * Retrieves a patient information
	 * 
	 * @param ssn SSN of the patient
	 * @return the object representing the patient
	 * @throws NoSuchPatient in case of no patient with matching SSN
	 */
	public String getPatient(String ssn) throws NoSuchPatient {
		Patient patient = patients.get(ssn);
		if (patient == null) {
			throw new NoSuchPatient();
		}
		return patient.toString();
	}

	/**
	 * Add a new doctor working at the clinic
	 * 
	 * @param first first name of the doctor
	 * @param last last name of the doctor
	 * @param ssn SSN number of the doctor
	 * @param docID unique ID of the doctor
	 * @param specialization doctor's specialization
	 */
	public void addDoctor(String first, String last, String ssn, int docID, String specialization) {
		Doctor doctor = new Doctor(first, last, ssn, docID, specialization);
		doctors.put(docID, doctor);
		patients.put(ssn, doctor);
	}

	/**
	 * Retrieves information about a doctor
	 * 
	 * @param docID ID of the doctor
	 * @return object with information about the doctor
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public String getDoctor(int docID) throws NoSuchDoctor {
		Doctor doctor = doctors.get(docID);
		if (doctor == null) {
			throw new NoSuchDoctor();
		}
		return doctor.toString();
	}
	
	/**
	 * Assign a given doctor to a patient
	 * 
	 * @param ssn SSN of the patient
	 * @param docID ID of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor exists with a matching ID
	 */
	public void assignPatientToDoctor(String ssn, int docID) throws NoSuchPatient, NoSuchDoctor {
		Patient patient = patients.get(ssn);
		if (patient == null) {
			throw new NoSuchPatient();
		}
		Doctor doctor = doctors.get(docID);
		if (doctor == null) {
			throw new NoSuchDoctor();
		}
		doctor.addPatientToDoctor(patient);
		patient.addDoctorToPatient(doctor);
	}
	
	/**
	 * Retrieves the id of the doctor assigned to a given patient.
	 * 
	 * @param ssn SSN of the patient
	 * @return id of the doctor
	 * @throws NoSuchPatient in case of not patient with matching SSN
	 * @throws NoSuchDoctor in case no doctor has been assigned to the patient
	 */
	public int getAssignedDoctor(String ssn) throws NoSuchPatient, NoSuchDoctor {
		Patient patient = patients.get(ssn);
		if (patient == null) {
			throw new NoSuchPatient();
		}
		Doctor doctor = patient.getDoctor();
		if (doctor == null) {
			throw new NoSuchDoctor();
		}
		return doctor.getDocID();
	}
	
	/**
	 * Retrieves the patients assigned to a doctor
	 * 
	 * @param id ID of the doctor
	 * @return collection of patient SSN
	 * @throws NoSuchDoctor in case the {@code id} does not match any doctor 
	 */
	public Collection<String> getAssignedPatients(int id) throws NoSuchDoctor {
		Doctor doctor = doctors.get(id);
		if (doctor == null) {
			throw new NoSuchDoctor();
		}
		return doctor.getPatients()
				.stream()
				.map(Patient::getSsn)
				.collect(toList());
	}

	/**
	 * Loads data about doctors and patients from the given stream.
	 * <p>
	 * The text file is organized by rows, each row contains info about
	 * either a patient or a doctor.</p>
	 * <p>
	 * Rows containing a patient's info begin with letter {@code "P"} followed by first name,
	 * last name, and SSN. Rows containing doctor's info start with letter {@code "M"},
	 * followed by badge ID, first name, last name, SSN, and specialization.<br>
	 * The elements on a line are separated by the {@code ';'} character possibly
	 * surrounded by spaces that should be ignored.</p>
	 * <p>
	 * In case of error in the data present on a given row, the method should be able
	 * to ignore the row and skip to the next one.<br>

	 * 
	 * @param path the path of the required file
	 * @throws IOException in case of IO error
	 */
	public void loadData(Reader reader) throws IOException {
		List<String> lines = null;
		try(BufferedReader in = new BufferedReader(reader)){
			lines = in.lines().collect(toList());
		}catch(IOException e) { 
			System.err.println(e.getMessage());
		}
	
		if(lines == null) return; 
	
		lines
		.forEach( r -> {
			String[] row = r.split(";");
			for (int i = 0; i < row.length; i++) {
				row[i] = row[i].trim();
			}
			
			try{
				if(row[0].equalsIgnoreCase("P")){
					addPatient(row[1],row[2],row[3]);
				}else
				if(row[0].equalsIgnoreCase("M")){
					addDoctor(row[2],row[3],row[4],Integer.parseInt(row[1]),row[5]);
				}else{
					System.err.println("Unrecognized line type");
				}
			}catch(ArrayIndexOutOfBoundsException e){
				System.err.println("Missing elements on the line");
			}catch(NumberFormatException e){
				System.err.println("Cannot parse integer value");
			}
		});
	}

	/**
	 * Retrieves the collection of doctors that have no patient at all, sorted in alphabetic order.
	 * 
	 * @return the collection of doctors with no patient sorted in alphabetic order (last name and then first name)
	 */
	public Collection<Integer> idleDoctors(){
		return doctors.values()
				.stream()
				.filter(d -> d.getPatients().isEmpty())
				.sorted(comparing(Doctor::getLast).thenComparing(Doctor::getFirst))
				.map(Doctor::getDocID)
				.collect(toList());
	}

	/**
	 * Retrieves the collection of doctors having a number of patients larger than the average.
	 * 
	 * @return  the collection of doctors
	 */
	public Collection<Integer> busyDoctors(){
		double average = doctors.values()
							.stream()
							.mapToInt( d -> d.getPatients().size()).average().orElse(0.0);
		return doctors.values()
				.stream()
				.filter(d -> d.getPatients().size() > average)
				.map(Doctor::getDocID)
				.collect(toList());
	}

	/**
	 * Retrieves the information about doctors and relative number of assigned patients.
	 * <p>
	 * The method returns list of strings formatted as "{@code ### : ID SURNAME NAME}" where {@code ###}
	 * represent the number of patients (printed on three characters).
	 * <p>
	 * The list is sorted by decreasing number of patients.
	 * 
	 * @return the collection of strings with information about doctors and patients count
	 */
	public Collection<String> doctorsByNumPatients(){
		return doctors.values()
				.stream()
				.sorted(comparing(d -> d.getPatients().size(), reverseOrder()))
				.map(d -> String.format("%3d", d.getPatients().size()) + " : " +d.getDocID() + " " + d.getLast() + " " + d.getFirst())
				.collect(toList());
	}
	
	/**
	 * Retrieves the number of patients per (their doctor's)  specialization 
	 * <p>
	 * The information is a collections of strings structured as {@code ### - SPECIALITY}
	 * where {@code SPECIALITY} is the name of the speciality and 
	 * {@code ###} is the number of patients cured by doctors with such speciality (printed on three characters).
	 * <p>
	 * The elements are sorted first by decreasing count and then by alphabetic specialization.
	 * 
	 * @return the collection of strings with specialization and patient count information.
	 */
	public Collection<String> countPatientsPerSpecialization(){
		return patients.values().stream()
				.filter(p->p.getDoctor()!=null)
				.collect(groupingBy( (Patient p) -> p.getDoctor().getSpecialization(),
									 ()->new TreeMap<String,Long>(reverseOrder()), counting()))
				.entrySet().stream()
				.sorted(comparing(Map.Entry::getValue,reverseOrder()))
				.map( e -> String.format("%3d", e.getValue()) + " - " + e.getKey() ) 
				.collect(toList());
	}
	
}
