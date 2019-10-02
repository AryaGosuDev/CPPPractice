

enum cutDir { vert = 0 , horiz = 1} ;

//eggs going in pre sorted
//recursive cut
void egg2dCut ( vector<vec2> eggs, float width , float height, size_t start, size_t end , cutDir d , vector<line> & cuts ) {
	if ( eggs.size() == 0 || eggs.size() == 1 ) return  ;
	//sort by x

	//base case
	if (start == end || start > end) return ;
	size_t mid = start + eggs.size() / 2 ;

	if ( d == cutDir.vert) {
		line cutLine ; cutLine.x = eggs[mid].x ; cutLine.height = height; cuts.push_back(cutLine) ;
		egg2dCut ( eggs, eggs[mid].x, height, start, mid, cutDir.horiz, cuts) ;
		egg2dCut ( eggs, width - eggs[mid].x, height, mid+1, end , cutDir.horiz, cuts ) ;

	}
	if ( d == cutDir.horiz ) {
		line cutLine ; cutLine.y = eggs[mid].y ; cutLine.width = width; cuts.push_back( cutLine );
		egg2dCut ( eggs, width, eggs[mid].y, start, mid, cutDir.vert, cuts) ;
		egg2dCut ( eggs, width, height - eggs[mid].y, mid+1, end , cutDir.vert, cuts ) ;
	}
}
