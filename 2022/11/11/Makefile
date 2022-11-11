CFLAGS = -DFLAG

SRC = main.c queue.c stack.c
EXEC_OBJECTS = $(SRC:.c=.o)

EXEC_FILE = exec

exec : $(EXEC_OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC_FILE) $(EXEC_OBJECTS)

DEBUG_DIR = .debug
DEBUG_EXEC = $(DEBUG_DIR)/$(EXEC_FILE)
# 预定义的函数 $(addprefix prefix, names...)
# 表示为每个 names 中的入参添加 prefix
DEBUG_OBJECTS = $(addprefix $(DEBUG_DIR)/, $(EXEC_OBJECTS))
DEBUG_FLAGS = -g -O0 -DDEBUG

debug : $(DEBUG_EXEC)

$(DEBUG_OBJECTS) : | $(DEBUG_DIR)

$(DEBUG_DIR) : 
			mkdir $(DEBUG_DIR)

# $@ 表示 target
# $< 表示 prerequisites 第一个参数
# $^ 表示 prerequisites 所有参数 
$(DEBUG_DIR)/%.o : %.c
				$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(DEBUG_EXEC) : $(DEBUG_OBJECTS)
			$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_EXEC) $^

clean : 
	rm -rf $(EXEC_FILE) $(EXEC_OBJECTS) $(DEBUG_DIR)