package diet;

/**
 * Represent a recipe of the diet.
 * 
 * A recipe consists of a a set of ingredients that are given amounts of raw materials.
 * The overall nutritional values of a recipe can be computed
 * on the basis of the ingredients' values and are expressed per 100g
 * 
 *
 */
public class Recipe implements NutritionalElement {
	
	private String name;
	private Food food;
	private double calories=0.0;
	private double proteins=0.0;
	private double carbs=0.0;
	private double fat=0.0;
	private double totalQuantity=0.0;
    
	/**
	 * Recipe constructor.
	 * The reference {@code food} of type {@link Food} must be used to
	 * retrieve the information about ingredients. 
	 * 
	 * @param nome unique name of the recipe
	 * @param food object containing the information about ingredients
	 */
	public Recipe(String name, Food food) {
		this.name=name;
		this.food=food;
		this.food.putRecipe(this);
	}
	
	/**
	 * Adds a given quantity of an ingredient to the recipe.
	 * The ingredient is a raw material defined with the {@code food}
	 * argument of the constructor.
	 * 
	 * @param material the name of the raw material to be used as ingredient
	 * @param quantity the amount in grams of the raw material to be used
	 */
	public void addIngredient(String material, double quantity) {
		NutritionalElement ingredient = food.getRawMaterial(material);
		calories+=ingredient.getCalories(quantity);
		proteins+=ingredient.getProteins(quantity);
		carbs+=ingredient.getCarbs(quantity);
		fat+=ingredient.getFat(quantity);
		totalQuantity+=quantity;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public double getCalories() {
		return (calories*100)/totalQuantity;
	}

	@Override
	public double getProteins() {
		return (proteins*100)/totalQuantity;
	}

	@Override
	public double getCarbs() {
		return (carbs*100)/totalQuantity;
	}

	@Override
	public double getFat() {
		return (fat*100)/totalQuantity;
	}

	/**
	 * Indicates whether the nutritional values returned by the other methods
	 * refer to a conventional 100g quantity of nutritional element,
	 * or to a unit of element.
	 * 
	 * For the {@link Recipe} class it must always return {@code true}:
	 * a recipe expressed nutritional values per 100g
	 * 
	 * @return boolean indicator
	 */
	@Override
	public boolean per100g() {
	    return true;
	}

}
