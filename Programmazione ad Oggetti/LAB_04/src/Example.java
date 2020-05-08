
import schools.Branch;
import schools.Community;
import schools.Municipality;
import schools.Region;
import schools.School;
import static java.util.stream.Collectors.*;


public class Example {

	public static void main(String[] args) throws Exception {

		Region region = new Region("Piemonte");
		
		Community cc = region.newCommunity("PoliTo Hills", Community.Type.COLLINARE);
		
		Municipality to = region.newMunicipality("Torino", "TO", cc);
		region.newMunicipality("Cuneo", "CN");

		for(Municipality m : region.getMunicipalies()){
			System.out.println("Created municipality " + m.getName() + 
							" part of community " + m.getCommunity().map(Community::getName).orElse("<none>"));
		}
		
		School s = region.newSchool("Liceum","TOLC01", 4, "Liceum school");
		region.newBranch(1234, to, "C.so Duca", 10129, s);
		region.newBranch(1235, to, "C.so Castelfidardo", 10129, s);
		
		System.out.println("Created school " + s.getName() + " with branches " +
							s.getBranches().stream().collect(mapping(Branch::getAddress,joining(",")))
				);
				

		Region r = new Region("Piemonte");
		
		r.readData("schools.csv");
		
		System.out.println("Loaded " + r.getSchools().size() + " schools");
		
		System.out.println("Count of schools by description");
		r.countSchoolsPerDescription().forEach( (k,v) -> System.out.println(k + ":" + v));

		System.out.println("Count branches per municipality");
		r.countBranchesPerMunicipality().forEach( (k,v) -> System.out.println(k + ":" + v));

		System.out.println("Count branches per municipality per province");
		r.countBranchesPerMunicipalityPerProvince().forEach( (k,v) -> System.out.println(k + ":" + v));

		System.out.println("Count schools per minicipality");
		r.countSchoolsPerMunicipality().forEach( System.out::println);

		System.out.println("Count schools by community");
		r.countSchoolsPerCommunity().forEach( System.out::println);
	}

}
