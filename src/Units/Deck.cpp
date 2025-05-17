#include "../../include/Deck.hpp"

Deck::Deck()
{
    current_no_units = 0;
    units = new Unit*[MAX_UNITS];
    isPicked = new bool[MAX_UNITS];
    
     // --- Outer Rectangle (Deck Background) ---
     rectangle = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 4);
     sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
     float outerRectWidth = 600; // Based on your positions (size.x/2 + 300) - (size.x/2 - 300)
     float outerRectHeight = 190; // Based on your positions (size.y - 10) - (size.y - 200)
     sf::Vector2f outerRectTL(windowSize.x / 2.f - outerRectWidth / 2.f, windowSize.y - outerRectHeight - 10); // Calculate TL dynamically
 
 // Adjusting outer rectangle vertices based on calculated TL and dimensions
     rectangle[0].position = outerRectTL; // Top-Left
     rectangle[1].position = outerRectTL + sf::Vector2f(0, outerRectHeight); // Bottom-Left
     rectangle[2].position = outerRectTL + sf::Vector2f(outerRectWidth, 0); // Top-Right
     rectangle[3].position = outerRectTL + sf::Vector2f(outerRectWidth, outerRectHeight); // Bottom-Right
 
     for(int i = 0; i < 4; i++){
         rectangle[i].color = sf::Color::Blue;
     }
 
      // --- Inner Rectangles (Unit Slots in Deck) ---
      const int vertices_per_rectangle = 6; // CORRECT: 6 vertices for a rectangle with Triangles
     
      inner_recs.setPrimitiveType(sf::PrimitiveType::Triangles); // CORRECT: Use Triangles for disconnected rectangles
      inner_recs.resize(vertices_per_rectangle * MAX_UNITS);      // CORRECT: Size the array for all 6*MAX_UNITS vertices
  
      float innerRectWidth = 70.f;  // Example width for inner rectangles
      float innerRectHeight = 100.f; // Example height
      float horizontalSpacing = 10.f; // Space between inner rectangles
      float padding_x = 20.f; // Padding from the left edge of the outer rectangle
      float padding_y = 20.f; // Padding from the top edge of the outer rectangle
  
      // Calculate the starting position for the first inner rectangle
      sf::Vector2f currentInnerRectPos = rectangle[0].position + sf::Vector2f(padding_x, padding_y);
  
      for(int i = 0; i < MAX_UNITS; ++i) // CORRECT: Loop once per rectangle
      {
          // Calculate the starting index for the 6 vertices of the current rectangle
          int startIndex = i * vertices_per_rectangle; // i * 6
  
          // Calculate the positions of the 4 corners for the current inner rectangle
          sf::Vector2f tl = currentInnerRectPos;
          sf::Vector2f bl = currentInnerRectPos + sf::Vector2f(0, innerRectHeight);
          sf::Vector2f tr = currentInnerRectPos + sf::Vector2f(innerRectWidth, 0);
          sf::Vector2f br = currentInnerRectPos + sf::Vector2f(innerRectWidth, innerRectHeight);
  
          // Add the 6 vertices for this rectangle to the VertexArray (using Triangles type)
          // Triangle 1: TL, BL, TR
          inner_recs[startIndex + 0].position = tl;
          inner_recs[startIndex + 1].position = bl;
          inner_recs[startIndex + 2].position = tr;
  
          // Triangle 2: TR, BL, BR
          inner_recs[startIndex + 3].position = tr; // Repeat TR
          inner_recs[startIndex + 4].position = bl; // Repeat BL
          inner_recs[startIndex + 5].position = br; // BR
  
          // Set color (or texture coords) for these 6 vertices
          sf::Color innerColor = sf::Color::Red; // Example color
          for(int j = 0; j < vertices_per_rectangle; ++j) // Loop 6 times for colors
          {
              inner_recs[startIndex + j].color = innerColor;
              // If using textures, set texture coordinates here for each vertex
              // inner_recs[startIndex + j].texCoords = calculateTextureCoords(...); 
          }
  
          // Move the starting position for the *next* inner rectangle
          currentInnerRectPos.x += innerRectWidth + horizontalSpacing; 
      }
      // AI USED : GPT 4o PROMPT: these are the my game cpp files but the inner rectangles in user class are not visible
  
}

void Deck::draw(sf::RenderWindow* window){
    window->draw(rectangle);
    window->draw(inner_recs);

    for(int i = 0; i < MAX_UNITS; i++){
        if (units[i]->getisActive()){
            units[i]->draw(window);
        }
    }
}

Unit** Deck::getUnits(){
    return units;
}

bool* Deck::getIsPicked(){
    return isPicked;
}

void Deck::setIsPicked(int pick){
    isPicked[pick] = true;
}
void Deck::addUnit(Unit* unit){
    if (current_no_units < 5){
        units[current_no_units] = unit;
        current_no_units++;
        std:: cout << "Unit added successfully\n";
        return;
    }

    std:: cout << "List full, please replace a unit to continue\n";
}

void Deck::replaceUnit(Unit* unit, Unit* to_be_replaced){
    for(int i = 0; i < current_no_units; i++){
        if (units[i] == to_be_replaced){
            units[i] = unit;
            std:: cout << "Unit successfully found and replaced\n";
            return;
        }
    }
    std:: cout << "Unit to be replaced not found\n";
}