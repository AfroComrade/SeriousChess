#include "../Constants/Constants.h"
#include "../Constants/GameEntities.h"

extern GameObject* selected_object;
extern int SelectedTile[2];
extern Owner current_player;

GameObject* detectObject(float mouse_x, float mouse_y, int current_player);
bool setMovableTile(int tileY, int tileX);

void setMovableForPawn();
void setMovableForKnight();
void setMovableForBishop();
void setMovableForRook();
void setMovableForKing();
void setMovableTiles(PieceType piece);
void removeMovableTiles();
bool checkWinCondition();
