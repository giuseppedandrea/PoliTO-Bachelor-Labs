import diet.Food;
import diet.NutritionalElement;
import diet.Menu;
import diet.Recipe;


public class ExampleApp {

    public static void main(String[] args)  {
    	
        Food food = new Food();
        food.defineRawMaterial("Sugar", 400, 0, 100, 0);
        food.defineRawMaterial("Mais", 70, 2.7, 12, 1.3);
        food.defineRawMaterial("Pasta", 350, 12, 72.2, 1.5);
        food.defineRawMaterial("Oil", 900, 0, 0, 100);
        food.defineRawMaterial("Nutella", 530, 6.8, 56, 31);
        
        System.out.println("Calories for the defined materials:");
        for(NutritionalElement e : food.rawMaterials()){
            System.out.println(e.getName() + " cal: " + e.getCalories());
        }
        
        food.defineProduct("Crackers", 111, 2.6, 17.2, 3.5);
        
        Recipe r = new Recipe("Pasta and Nutella", food);
        r.addIngredient("Pasta", 70);
        r.addIngredient("Nutella", 30);
        
        Menu menu = new Menu("M1", food);
        menu.addRecipe("Pasta and Nutella", 50);
        menu.addProduct("Crackers");
        
        System.out.println("Nutritional value for menu " + menu.getName() + 
                "\n\tCalories : " + menu.getCalories() +
                "\n\tCarbs    : " + menu.getCarbs() +
                "\n\tFat      : " + menu.getFat() +
                "\n\tProteins : " + menu.getProteins() +
                "."
                );

    }

}
