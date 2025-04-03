#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
	insert_at_tail(&(q->data), serialize(state));
	return;
}

struct game_state dequeue(struct queue *q) { 
	
	return deserialize(remove_from_head(&(q->data)));
}

int number_of_moves(struct game_state start) {

	struct queue q;
	struct linked_list l;

	l.head = NULL;

	

	q.data = l;

	enqueue(&q, start);

	struct game_state game;
	struct game_state newGame;
	

	int col = 0;
	int row = 0;
	int flag = 0;

	do
	{
		game = dequeue(&q);
		col = 0;
		row = 0;
		flag = 0;

		for(int i = 1; i < 17; i++)
		{
			col++;
			if(col == 4)
			{
				col = 0;
				row++;
			}

			if((int) game.tiles[row][col] != i % 16)
			{
				flag = 1;
			}
		}

		if(flag == 0)
		{
			if((int) game.empty_row != 0)
			{
				newGame = deserialize(serialize(game));
				move_up(&newGame);
				enqueue(&q, newGame);
			}

			if((int) game.empty_row != 3)
			{
				newGame = deserialize(serialize(game));
				move_down(&newGame);
				enqueue(&q, newGame);

			}

			if((int) game.empty_col != 0)
			{
				newGame = deserialize(serialize(game));
				move_left(&newGame);
				enqueue(&q, newGame);
			}

			if((int) game.empty_row != 3)
			{
				newGame = deserialize(serialize(game));
				move_right(&newGame);
				enqueue(&q, newGame);
			}

		}

	}
	while(flag);

	return game.num_steps; 
}
