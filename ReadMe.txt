Aside from functions I was provided I added additional helpers such as randomLevel, findById, getHead.
-> randomLevel - to generate skip list levels during insertion
-> findById - find a student node by ID when updating and removing, making it easier and optimal solution as the same code can be used twice.
-> getHead - allow Student Database to traverse the skip list in functions such as get_top_k_students(), get_rank(), and range_query()

Considerations:
1. Duplicate IDs were checked before inserting.
2. Memory leaks were avoided by dynamic memory realised in destructors.
