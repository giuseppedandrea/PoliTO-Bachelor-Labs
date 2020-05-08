package diet;

/**
 * Represents a complete menu.
 * 
 * It can be made up of both packaged products and servings of given recipes.
 *
 */
public class Menu implements NutritionalElement {

	private String name;
	private Food food;
	private double calories=0.0;
	private double proteins=0.0;
	private double carbs=0.0;
	private double fat=0.0;

	/**
	 * Menu constructor.
	 * The reference {@code food} of type {@link Food} must be used to
	 * retrieve the information about recipes and products 
	 * 
	 * @param nome unique name of the menu
	 * @param food object containing the information about products and recipes
	 */
	public Menu(String name, Food food){
		this.name=name;
		this.food=food;
	}
	
	/**
	 * Adds a given serving size of a recipe.
	 * The recipe is a name of a recipe defined in the {@code food}
	 * argument of the constructor.
	 * 
	 * @param recipe the name of the recipe to be used as ingredient
	 * @param quantity the amount in grams of the recipe to be used
	 */
	public void addRecipe(String recipe, double quantity) {
		NutritionalElement recipeToAdd = food.getRecipe(recipe);
		calories+=recipeToAdd.getCalories(quantity);
		proteins+=recipeToAdd.getProteins(quantity);
		carbs+=recipeToAdd.getCarbs(quantity);
		fat+=recipeToAdd.getFat(quantity);	
	}

	/**
	 * Adds a unit of a packaged product.
	 * The product is a name of a product defined in the {@code food}
	 * argument of the constructor.
	 * 
	 * @param product the name of the product to be used as ingredient
	 */
	public void addProduct(String product) {
		NutritionalElement productToAdd = food.getProduct(product);
		calories+=productToAdd.getCalories();
		proteins+=productToAdd.getProteins();
		carbs+=productToAdd.getCarbs();
		fat+=productToAdd.getFat();
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public double getCalories() {
		return calories;
	}

	@Override
	public double getProteins() {
		return proteins;
	}

	@Override
	public double getCarbs() {
		return carbs;
	}

	@Override
	public double getFat() {
		return fat;
	}

	/**
	 * Indicates whether the nutritional values returned by the other methods
	 * refer to a conventional 100g quantity of nutritional element,
	 * or to a unit of element.
	 * 
	 * For the {@link Menu} class it must always return {@code false}:
	 * nutritional values are provided for the whole menu.
	 * 
	 * @return boolean indicator
	 */
	@Override
	public boolean per100g() {
		return false;
	}
}
