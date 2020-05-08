package clinic.demo;
import clinic.Clinic;
import clinic.NoSuchDoctor;
import clinic.NoSuchPatient;


public class DemoApp {

	public static void main(String[] args) throws NoSuchPatient, NoSuchDoctor {

		Clinic clinic = new Clinic();

		clinic.addPatient("Alice", "Green", "ALCGRN00A00B123Z");
		System.out.println(clinic.getPatient("ALCGRN00A00B123Z")); // Green Alice (ALCGRN00A00B123Z)
		clinic.addPatient("Robert", "Smith", "RBTSMT00A00B123Z");
		clinic.addPatient("Steve", "Moore", "STVMRE00A00B123Z");
		clinic.addPatient("Susan", "Madison", "SSNMDS00A00B123Z");
		

		clinic.addDoctor("George", "Sun","SNUGRG00A00B123Z", 14,"Physician");
		System.out.println(clinic.getDoctor(14)); // Sun George (SNUGRG00A00B123Z) [14]: Physician
		clinic.addDoctor("Kate", "Love", "LVOKTA00A00B123Z",86,"Physician");
		clinic.addDoctor("Felix", "Donothing", "FLXNTH00A00B123Z",9,"Homeopatist");

		clinic.assignPatientToDoctor("SSNMDS00A00B123Z", 86);
		clinic.assignPatientToDoctor("ALCGRN00A00B123Z", 14);
		clinic.assignPatientToDoctor("RBTSMT00A00B123Z", 14);
		clinic.assignPatientToDoctor("STVMRE00A00B123Z", 14);
		System.out.println(clinic.getAssignedDoctor("SSNMDS00A00B123Z")); // 86
		System.out.println(clinic.getAssignedPatients(14)); // [ALCGRN00A00B123Z, STVMRE00A00B123Z, RBTSMT00A00B123Z]
		
		try {
			clinic.getDoctor(-1);
		} catch (NoSuchDoctor ex) {
			System.out.println("Expected exception: " + ex);
		}
		System.out.println(clinic.idleDoctors()); // [9]
		System.out.println(clinic.busyDoctors()); // [14]
		
		System.out.println(clinic.doctorsByNumPatients()); // [  3 : 14 Sun George,   1 : 86 Love Kate]
		System.out.println(clinic.countPatientsPerSpecialization()); // [  4 - Physician]
	}

}
