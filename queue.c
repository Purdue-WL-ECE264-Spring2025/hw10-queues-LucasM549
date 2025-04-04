#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
	//printf("%p", &(q->data));
	//printf("test2");
	
	insert_at_tail(&(q->data), serialize(state));
	return;
}

struct game_state dequeue(struct queue *q) { 
	
	return deserialize(remove_from_head(&(q->data)));
}

struct game_state copyGame(struct game_state game)
{	
	struct game_state newGame;

	//printf("test(1)\n");
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			newGame.tiles[i][j] = game.tiles[i][j];
		}
	}

	newGame.empty_row = game.empty_row;
	newGame.empty_col = game.empty_col;
	newGame.num_steps = game.num_steps;

	return newGame;
} 

int number_of_moves(struct game_state start) {

//struct queue q;
	struct linked_list l;

	//return 3;

	l.head = NULL;
	
	insert_at_tail(&l, serialize(start));

	//q.data = l;

	//printf("%p", q.data)

	struct game_state game;
	struct game_state newGame;	

	int col = 0;
	int row = 0;
	int flag = 0;

	do
	{
		/*
		int k = 0;

		printf("[ ");
  	for (struct list_node *cur = l.head; cur != NULL; cur = cur->next) {
    	
			printf("%d ", deserialize(cur->value).num_steps);
			k++;
			                 //deserialize
  	}	
  	printf("] %d\n", k);
		
		k = 0;
		*/

		game = deserialize(remove_from_head(&l));
		/*
		printf("[ ");
  	for (struct list_node *cur = l.head; cur != NULL; cur = cur->next) {
    	
			printf("%d ", deserialize(cur->value).num_steps);
			k++;
			                 //deserialize
  	}	
  	printf("] %d\n\n", k);
		*/
		



		col = 0;
		row = 0;
		flag = 1;

		for(int i = 1; i < 17; i++)
		{
			//printf("%d = %d?\n", game.tiles[row][col], i);

			if((int) game.tiles[row][col] != i % 16)
			{
				flag = 0;
			}

			if(col == 4)
			{
				col = 0;
				row++;
			}
			
			col++;
			
		}
		
		
		//printf("flag: %d", flag);

		if(flag == 0)
		{
			//printf("test2\n");
			if((int) game.empty_row != 3)
			{
				newGame = copyGame(game);
				move_up(&newGame);
				insert_at_tail(&l, serialize(newGame));
			}

			if((int) game.empty_row != 0)
			{
				newGame = copyGame(game);
				move_down(&newGame);
				insert_at_tail(&l, serialize(newGame));
			}

			if((int) game.empty_col != 3)
			{
				newGame = copyGame(game);
				move_left(&newGame);
				insert_at_tail(&l, serialize(newGame));
			}

			if((int) game.empty_col != 0)
			{
				newGame = copyGame(game);
				move_right(&newGame);
				insert_at_tail(&l, serialize(newGame));
			}

		}

		//printf("test(2)");

	}
	
	while(!flag);

	//printf("test 3\n");

	return game.num_steps; 
}


