class TrieNode {
public:
    char data;
    vector<TrieNode*> children;
    bool end;

    TrieNode(char data) {
        this->data = data;
        children.resize(26, NULL);
        end = false;
    }
}; 

class Trie {
    TrieNode *root;
public:
    Trie() {
        root = new TrieNode('\0');
    }
    void insert(string &word) {
        TrieNode *temp = root;
        for(int i=0; i<word.size(); i++){
            int index = word[i] - 'a';
            if(temp->children[index] == NULL){
                temp->children[index] = new TrieNode(word[i]);
            }
            temp = temp->children[index];
        }
        temp->end = true;
    }
private:
    void dfs(TrieNode *temp, string &word, vector<string> &ans){
        if(temp->end) {
            ans.push_back(word);
        }

        for(int i=0; i<26; i++){
            if(temp->children[i]){
                word.push_back(i+'a');
                dfs(temp->children[i], word, ans);
                word.pop_back();
            }
        }
    }
public:
    vector<string> getwords(string &prefix){
        TrieNode *temp = root;
        vector<string> res;

        for(int i=0; i<prefix.size(); i++){
            int index = prefix[i] - 'a';
            if(temp->children[index] == NULL){
                return res;
            }
            temp = temp->children[index];
        }
        dfs(temp, prefix, res);
        return res;
    }
};