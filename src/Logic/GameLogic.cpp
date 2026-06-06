#include "../Constants/Constants.h"
#include "../Constants/GameEntities.h"
#include "../Init/loaders.h"

GameObject* selected_object = nullptr;
int SelectedTile[2] = {};

GameObject* detectObject(float mouse_x, float mouse_y, int current_player)
{
    if ((mouse_x > BOARD_WIDTH)
        || (mouse_y > BOARD_HEIGHT))
    {
        return nullptr;
    }

    int tile_x = mouse_x / TILE_WIDTH;
    int tile_y = mouse_y / TILE_HEIGHT;

    GameObject* obj = tiles[tile_y][tile_x]->obj;

    if ((obj != nullptr)
        && (obj->owner == current_player))
    {
        tiles[tile_y][tile_x]->obj = nullptr;
        return obj;
    }

    return nullptr;
}

bool setMovableTile(int tileY, int tileX)
{
    bool hasObject = false;

    if ((tileY < TILE_Y) && (tileY >= 0)
        && (tileX < TILE_X) && (tileX >= 0))
    {
        if ((tiles[tileY][tileX]->obj != nullptr)
            && (tiles[tileY][tileX]->obj->owner != selected_object->owner))
        {
            tiles[tileY][tileX]->toMove = true;
        }
        else if (tiles[tileY][tileX]->obj == nullptr)
            tiles[tileY][tileX]->toMove = true;

        if (tiles[tileY][tileX]->obj != nullptr)
        {
            hasObject = true;
        }
    } else {
        hasObject = true;
    }

    return hasObject;
}

void setMovableForPawn()
{
    int toMove = 1;
    bool firstMove = false;
    if (selected_object->owner == BLACK)
    {
        toMove = -1;
        if (SelectedTile[0] == 1)
            firstMove = true;
    }
    else if ((selected_object->owner == WHITE)
        && (SelectedTile[0] == 6))
        firstMove = true;

    int tileY = SelectedTile[0] - toMove;
    int tileX = SelectedTile[1];
    if (tileX-1 >= 0)
    {
        if (tiles[tileY][tileX-1]->obj != nullptr)
            setMovableTile(tileY,tileX-1);
    }
    if (tileY+1 < TILE_X)
    {
        if (tiles[tileY][tileX+1]->obj != nullptr)
            setMovableTile(tileY,tileX+1);
    }

    if(tiles[tileY][tileX]->obj == nullptr)
    {
        setMovableTile(tileY, tileX);

        if (firstMove)
        {
            tileY = tileY - toMove;
            setMovableTile(tileY, tileX);
        }
    }
}

void setMovableForKnight()
{
    int tileY = SelectedTile[0]-1;
    int tileX = SelectedTile[1]-2;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]-1;
    tileX = SelectedTile[1]+2;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]-2;
    tileX = SelectedTile[1]-1;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]-2;
    tileX = SelectedTile[1]+1;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]+1;
    tileX = SelectedTile[1]-2;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]+1;
    tileX = SelectedTile[1]+2;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]+2;
    tileX = SelectedTile[1]-1;
    setMovableTile(tileY, tileX);

    tileY = SelectedTile[0]+2;
    tileX = SelectedTile[1]+1;
    setMovableTile(tileY, tileX);
}

void setMovableForBishop()
{
    int tileY = SelectedTile[0];
    int tileX = SelectedTile[1];

    bool hasObject = false;
    int counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY-1;
        tileX = tileX-1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY+1;
        tileX = tileX-1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY+1;
        tileX = tileX+1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY-1;
        tileX = tileX+1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }
}

void setMovableForRook()
{
    int tileY = SelectedTile[0];
    int tileX = SelectedTile[1];

    bool hasObject = false;
    int counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY-1;
        tileX = tileX;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY+1;
        tileX = tileX;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY;
        tileX = tileX+1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }

    tileY = SelectedTile[0];
    tileX = SelectedTile[1];
    hasObject = false;
    counter = 8;
    while (!hasObject && (counter > 0))
    {
        tileY = tileY;
        tileX = tileX-1;
        hasObject = setMovableTile(tileY, tileX);
        counter--;
    }
}

void setMovableForKing()
{
    int tileY = SelectedTile[0];
    int tileX = SelectedTile[1];

    setMovableTile(tileY+1, tileX);
    setMovableTile(tileY+1, tileX+1);
    setMovableTile(tileY, tileX+1);
    setMovableTile(tileY-1, tileX+1);
    setMovableTile(tileY-1, tileX);
    setMovableTile(tileY-1, tileX-1);
    setMovableTile(tileY, tileX-1);
    setMovableTile(tileY+1, tileX-1);
}

void setMovableTiles(PieceType piece)
{
    if (piece == PAWN)
        setMovableForPawn();
    else if (piece == KNIGHT)
        setMovableForKnight();
    else if (piece == BISHOP)
        setMovableForBishop();
    else if (piece == ROOK)
        setMovableForRook();
    else if (piece == KING)
        setMovableForKing();
    else if (piece == QUEEN)
    {
        setMovableForBishop();
        setMovableForRook();
    }
}

void removeMovableTiles()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            tiles[x][y]->toMove = false;
        }
    }
}

bool checkWinCondition()
{
    bool blackKingFound = false;
    bool whiteKingFound = false;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            GameObject* obj = tiles[x][y]->obj;
            if (obj == nullptr)
                continue;

            if ((obj->pieceType == KING)
                && (obj->owner == BLACK))
                blackKingFound = true;
            else if ((obj->pieceType == KING)
                && (obj->owner == WHITE))
                whiteKingFound = true;
        }
    }
    if ((blackKingFound == false)
        || whiteKingFound == false)
        return true;

    return false;
}
