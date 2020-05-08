package schools;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

// Hint: to write compact stream expressions
// you can include the following
import static java.util.stream.Collectors.*;
import static java.util.Comparator.*;

/**
 * Represents the region and serves as a facade class
 * for the package.
 * 
 * It provides factory methods for creating instances of
 * {@link Community}, {@link Municipality}, {@link School}, and {@link Branch}
 *
 */
public class Region {
	
	private String name;
	Collection<Community> communities = new LinkedList<Community>();
	Collection<Municipality> municipalities = new LinkedList<Municipality>();
	Collection<School> schools = new LinkedList<School>();
	Collection<Branch> branchs = new LinkedList<Branch>();
	
	/**
	 * Creates a new region with the given name.
	 * @param name the name of the region
	 */
	public Region(String name){
		this.name = name;
	}
	
	/**
	 * Getter method
	 * @return the name of the region
	 */
	public String getName(){
		return name;
	}
	
	/**
	 * Retrieves all schools in the region
	 * @return collection of schools
	 */
	public Collection<School> getSchools() {
		return schools;
	}
	
	/**
	 * Retrieves all the communities
	 * @return the collection of all communities
	 */
	public Collection<Community> getCommunities() {
		return communities;
	}
	
	/**
	 * Retrieves all municipalities in the region
	 * @return the collection of municipalities
	 */
	public Collection<Municipality> getMunicipalies() {
		return municipalities;
	}
	
	
	// factory methods
	
	/**
	 * Factory method that build a new community of the given type.
	 * The type is {@link Community.Type}
	 * 
	 * @param name name of the community
	 * @param type type of the community
	 * @return the new created community
	 */
	public Community newCommunity(String name, Community.Type type){
		Community community = new Community(name, type);
		communities.add(community);
		return community;
	}

	/**
	 * Factory method that build a new municipality.
	 * 
	 * @param nome 		name of the municipality
	 * @param province 	province of the municipality
	 * @return the new created municipality
	 */
	public Municipality newMunicipality(String nome, String province){
		return newMunicipality(nome, province, null);
	}
	
	/**
	 * Factory methods, that build a new municipality that
	 * is part of a community.
	 * 
	 * @param nome 		name of the municipality
	 * @param province 	province of the municipality
	 * @param comunita  community the municipality belongs to 
	 * @return the new created municipality
	 */
	public Municipality newMunicipality(String nome, String province, Community comunita){
		Municipality municipality = new Municipality(nome, province, comunita);
		municipalities.add(municipality);
		if (comunita != null) {
			comunita.addMunicipaly(municipality);
		}
		return municipality;
	}
	
	/**
	 * Factory method that creates a new school
	 * 
	 * @param name    name of the school
	 * @param code    code of the school
	 * @param grade	  grade of the school (1 to 4)
	 * @param description  description of the school
	 * 
	 * @return a new school object
	 */
	public School newSchool(String name, String code, int grade, String description){
		School school = new School(name, code, grade, description);
		schools.add(school);
		return school;
	}
	
	/**
	 * Factory method that creates a new school branch
	 * 
	 * @param regionalCode	regional code of the branch
	 * @param municipality	municipality where the branch is located
	 * @param address		address of the branch
	 * @param zipCode		zip code of the branch
	 * @param school		school the branch is part of
	 * @return	the new created branch
	 */
	public Branch newBranch(int regionalCode, Municipality municipality, 
							String address, int zipCode, School school)	{
		Branch branch = new Branch(regionalCode, municipality, address, zipCode, school);
		branchs.add(branch);
		school.addBranch(branch);
		return branch;
	}
	
	/**
	 * Load data from a file.
	 * 
	 * The file must be a CSV file and it is supposed to contain the following fields:
	 * <ul>
	 *  <li>{@code "Provincia"},   (province)
	 *  <li>{@code "Comune"},		(municipality)
	 *  <li>{@code "Grado Scolastico"}, (school grade)
	 *  <li>{@code "Descrizione Scuola"}, (school description)
	 *  <li>{@code "Cod Sede"}, (branch code)
	 *  <li>{@code "Cod Scuola"}, (school code)
	 *  <li>{@code "Denominazione Scuola"}, (name of the school)
	 *  <li>{@code "Indirizzo e n. civico"}, (address of the branch)
	 *  <li>{@code "C.A.P."}, (zip code of the branch)
	 *  <li>{@code "Comunita Collinare"}, (Hill community)
	 *  <li>{@code "Comunita Montana"},  (Mountain community)
	 * </ul>
	 * 
	 * @param file the path of the file
	 */
	public void readData(String file) {
		List<String> lines = null;
		try(BufferedReader in = new BufferedReader(new FileReader(file))){
			lines = in.lines().collect(toList());
		}catch(IOException e) { System.err.println(e.getMessage()); }
	
		if(lines == null) return; 
		
		// each item of the list contains a line of
		// the CSV file that can be split using "," as separator
		String[] header = lines.remove(0).split(",");
		Map<String,Integer> h2i = new HashMap<>();
		for(int i=0; i<header.length; ++i){
			h2i.put(header[i], i);
		}		
		
		lines
		.forEach( r -> {
			String[] row = r.split(",");
			
			Community community;
			if ((row.length - 1) == h2i.get("Comunita Collinare")) {
				community = communities.stream().filter(c -> c.getName().equals(row[h2i.get("Comunita Collinare")])).findFirst().orElseGet(() -> newCommunity(row[h2i.get("Comunita Collinare")], Community.Type.COLLINARE));
			} else if ((row.length - 1) == h2i.get("Comunita Montana")) {
				community = communities.stream().filter(c -> c.getName().equals(row[h2i.get("Comunita Montana")])).findFirst().orElseGet(() -> newCommunity(row[h2i.get("Comunita Montana")], Community.Type.MONTANA));
			} else {
				community = null;
			}
			
			Municipality municipality = municipalities
					.stream()
					.filter(m -> m.getName().equals(row[h2i.get("Comune")]))
					.findFirst()
					.orElseGet(() -> newMunicipality(row[h2i.get("Comune")], row[h2i.get("Provincia")], community));
			
			School school = schools
					.stream()
					.filter(s -> s.getCode().equals(row[h2i.get("Cod Scuola")]))
					.findFirst()
					.orElseGet(() -> newSchool(row[h2i.get("Denominazione Scuola")], row[h2i.get("Cod Scuola")], Integer.parseInt(row[h2i.get("Grado Scolastico")]), row[h2i.get("Descrizione Scuola")]));
			
			newBranch(Integer.parseInt(row[h2i.get("Cod Sede")]), municipality, row[h2i.get("Indirizzo e n. civico")], Integer.parseInt(row[h2i.get("C.A.P.")]), school);
		});
	
	}


	/**
	 * Counts how many schools there exist for each description
	 * @return a map of school count vs. description
	 */
	public Map<String,Long>countSchoolsPerDescription(){
		return schools
				.stream()
				.collect(groupingBy(s -> s.getDescription(), counting()));
	}

	/**
	 * Count how many school branches there exist for each municipality
	 * @return a map of branch count vs. municipality
	 */
	public Map<String,Long>countBranchesPerMunicipality(){
		return schools
				.stream()
				.flatMap(s -> s.getBranches().stream())
				.collect(groupingBy(s -> s.getMunicipality().getName(), counting()));
	}

	/**
	 * Counts the number of school branches per municipality
	 * and groups them by province.
	 * @return a map of maps the inner reports count of branches vs. municipality
	 * 			the outer reports provinces as keys
	 */
	public Map<String,Map<String,Long>>countBranchesPerMunicipalityPerProvince(){
		return schools.stream()
				.map(School::getBranches)
				.flatMap(Collection::stream)
				.collect(groupingBy(s->s.getMunicipality().getProvince(), 
							groupingBy(s->s.getMunicipality().getName(),counting())));
	}

	/**
	 * returns a list of strings with format
	 * {@code "### - XXXXXX"}, where 
	 * {@code ###} represents the number of schools (not branches)
	 * and {@code XXXXXX} represents the name of the municipality.
	 * If a school has more than one branch in a municipality
	 * it must be counted only once.
	 * 
	 * @return a collection of strings with the counts
	 */
	public Collection<String> countSchoolsPerMunicipality(){
		return schools.stream()
					.map(School::getBranches)
					.flatMap(Collection::stream)
					.collect(groupingBy(s -> s.getMunicipality().getName(),
									 mapping(Branch::getSchool,collectingAndThen(toSet(), Set::size))))
					.entrySet().stream()
					.map(e -> e.getValue()+ " - "+e.getKey())
					.collect(toList());
	}
	
	/**
	 * returns a list of strings with format
	 * {@code "### - XXXXXX"}, where 
	 * {@code ###} represents the number of schools (not branches)
	 * and {@code XXXXXX} represents the name of the community.
	 * They are sorted by descending number of schools.
	 * The list must contain only schools having at least
	 * a branch in a municipality part of a community.
	 * 
	 * @return a collection of strings with the counts
	 */
	public List<String> countSchoolsPerCommunity() {
		return schools.stream()
				.map(School::getBranches)
				.flatMap(Collection::stream)
				.filter(s->s.getMunicipality().getCommunity().isPresent() )
				.collect(groupingBy(s->s.getMunicipality().getCommunity().get().getName(),
									 mapping(Branch::getSchool,collectingAndThen(toSet(), Set::size))))
				.entrySet().stream()
				.sorted(comparing(Map.Entry::getValue,reverseOrder()))
				.map(e -> e.getValue()+ " - "+e.getKey())
				.collect(toList());
	}
	
}
