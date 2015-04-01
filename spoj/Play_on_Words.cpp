//http://www.spoj.com/problems/WORDS1/
#include <stdio.h>
#include <string.h>

bool check();
bool haveEulerPath(char start_node);
signed char getStartNode();
void reset();
void addEdge(char index_from, char index_to);

unsigned int in_degree[26], out_degree[26], no_duplicate_out_degree[26];
unsigned int edge_count;
char edges[26];
signed char graph[26][26];
char stack[26*26];
unsigned int stack_index = -1;

void push(char t);
void pop();
char& top();
bool stack_is_empty();

int main() {
    int test_count;
    char word[1001];
    scanf("%d", &test_count);
    for(int i = 0; i < test_count; i++)
    {
        reset();
        int word_count;
        scanf("%d", &word_count);
        for(int j = 0; j < word_count; j++)
        {
            scanf("%s", word);
            addEdge(word[0] - 'a', word[strlen(word) - 1] - 'a');
        }
        if(!check()) printf("The door cannot be opened.\n");
        else printf("Ordering is possible.\n");
    }
    return 0;
}

bool check(){
    signed char start_node = getStartNode();
    if(start_node >= 0)
        return haveEulerPath(start_node);
    return false;
}

bool haveEulerPath(char start_node)
{
    unsigned int visited_edges = 0;
    push(start_node);
    while(!stack_is_empty())
    {
        char& current = top();
        signed char next = edges[current];
        if(next == 26) //check if point to nothing (26 = null)
        {
            //remove it and continue
            pop();
            continue;
        }
        //point the from_node last edge to the prev edge
        edges[current] = graph[current][next];
        //push linked node to stack and increment visited edges
        push((char)next);
        visited_edges++;
    }
    return visited_edges == edge_count;
}
void reset()
{
    memset(in_degree, 0, sizeof in_degree);
    memset(out_degree, 0, sizeof out_degree);
    memset(no_duplicate_out_degree, 0, sizeof no_duplicate_out_degree);
    memset(edges, 26, sizeof edges);
    memset(graph, -1, sizeof(signed char) * 26 * 26);
    edge_count = 0;
}
void addEdge(char from_index, char to_index)
{
    signed char & e = graph[from_index][to_index];
    out_degree[from_index]++;
    in_degree[to_index]++;
    //configure edges
    if(e == -1)
    {
        no_duplicate_out_degree[from_index]++;
        e = edges[from_index];
        edges[from_index] = to_index;
    }
}
signed char getStartNode(){
    unsigned int odd_count = 0;
    signed char index = -1;
    int in = -1;
    int out = -1;
    int tmp = 0;
    //check in and out degree of nodes
    for(int i = 0; i < 26; i++)
    {
        unsigned int& in_deg = in_degree[i];
        unsigned int& out_deg = out_degree[i];
        edge_count += no_duplicate_out_degree[i];

        if(in_deg + out_deg == 0)
        {
            continue;
        }
        index = i;
        tmp = in_deg - out_deg;
        //check if output node (input greater than output by 1)
        if(tmp == 1)
        {
            odd_count++;
            out = index;
        }
        else if(tmp == -1)
        {
            odd_count++;
            in = index;
        }
        else if(in_deg!=out_deg)
        {
            return -1;
        }
    }
    //all are even return any node
    if(odd_count == 0)
        return index;
    // all even 2 odd return any of the odd
    if(odd_count ==2 && in >= 0 && out >= 0)
    {
        return in;
    }
    //something not applicable return -1;
    return -1;
}

void push(char t)
{
    stack[++stack_index] = t;
}
void pop(){
    stack_index--;
}
char& top(){
    return stack[stack_index];
}

bool stack_is_empty()
{
    return stack_index == -1;
}
