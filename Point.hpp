			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Point.hpp"							//
			//														//
			//			Författad av: Andreas Sehr 2002,01,07		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//////////////////////////////////////////////////////////


class Point {
	public:
		void setX ( int initialX ) { x = initialX; }
		void setY ( int initialY ) { y = initialY; }

		int getX () { return x; }
		int getY () { return y; }

	private:
		int x, y;
};
