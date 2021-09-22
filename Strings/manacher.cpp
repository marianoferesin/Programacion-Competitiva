pair<vector <int>, vector <int>> manacher(string s){
	int n = s.size();
	vector<int> d1(n); //palindromes with character in the middel
	/*
	i is the index of the center letter of the current palindrome.
	d1[] stores the odd palindromes. So, if i exceeds r, k is initialized to 1, as a single letter is a palindrome in itself. For d2[], k will be initialized to 0.
	If i does not exceed r, k is either initialized to the d1[j], where j is the mirror position of i in (l,r), or k is restricted to the size of the "outer" palindrome.
	The while loop denotes the trivial algorithm. We launch it irrespective of the value of k.
	If the size of palindrome centered at i is x, then d1[i] stores (x+1)/2
	 */
	
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
			k++;
		}
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	
	vector<int> d2(n);//palindromes without character in the middel
	
	/*
	 Since an even palidrome will have two centers, i is the latter of the two center indices.
	if i exceeds r, k is initialized to 0, as a single letter is not an even palindrome.
	If the size of palindrome centered at i is x, then d2[i] stores x/2 
	 */
	
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
			k++;
		}
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
	return {d1,d2};
}
