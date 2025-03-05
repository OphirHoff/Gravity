typedef enum {
	EXPR_ADD,
	EXPR_SUBTRACT,
	EXPR_DIVIDE,
	EXPR_MULTIPLY,
	EXPR_VALUE,
	EXPR_VAR,
	EXPR_ASSIGN, 
	EXPR_LIST
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	float value;
	
	// For variables
	char *var_name;
	
	// For Expression lists
	struct expr *list;
};

// Function Declarations
struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);
struct expr *expr_create_dval(float value);
struct expr *expr_create_ival(int value);
struct expr * expr_create_var (char *name);