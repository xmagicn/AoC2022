#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <stack>
#include <set>
#include <algorithm>
#include <functional>

// Unused Param
#pragma warning( disable : 4100 )

int Year22Day1Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrentSum = 0;
	int CurrentMax = 0;

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.compare( "" ) )
		{
			CurrentSum += stoi( Line );
		}
		else
		{
			if ( CurrentSum > CurrentMax )
			{
				CurrentMax = CurrentSum;
			}
			CurrentSum = 0;
		}
	}

	myfile.close();

	return CurrentMax;
}

int Year22Day1Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrentSum = 0;

	std::vector<int> TopFour;

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.compare( "" ) )
		{
			CurrentSum += stoi( Line );
		}
		else
		{
			if ( TopFour.size() < 4 )
			{
				TopFour.push_back( CurrentSum );
			}
			else
			{
				TopFour[0] = CurrentSum;
				std::sort( TopFour.begin(), TopFour.end() );
			}
			CurrentSum = 0;
		}
	}

	if ( TopFour.size() < 4 )
	{
		TopFour.push_back( CurrentSum );
	}
	else
	{
		TopFour[0] = CurrentSum;
	}
	std::sort( TopFour.begin(), TopFour.end() );

	myfile.close();

	return TopFour[1] + TopFour[2] + TopFour[3];
}

struct RPSMatch
{
	enum class RPSVal
	{
		Rock = 1,
		Paper = 2,
		Scissors = 3,
	};

	void SetOpponent( char Val )
	{
		if ( Val == 'A' )
			Opponent = RPSVal::Rock;
		else if ( Val == 'B' )
			Opponent = RPSVal::Paper;
		else if ( Val == 'C' )
			Opponent = RPSVal::Scissors;
	}

	void SetSelf( char Val )
	{
		if ( Val == 'X' )
			Self = RPSVal::Rock;
		else if ( Val == 'Y' )
			Self = RPSVal::Paper;
		else if ( Val == 'Z' )
			Self = RPSVal::Scissors;
	}

	int GetSelfResult() const
	{
		int Output = static_cast< int >( Self );

		if ( Opponent == Self )
		{
			Output += 3;
		}
		else if ( Opponent == RPSVal::Rock && Self == RPSVal::Paper
			|| Opponent == RPSVal::Paper && Self == RPSVal::Scissors
			|| Opponent == RPSVal::Scissors && Self == RPSVal::Rock )
		{
			Output += 6;
		}

		return Output;
	}

	void ForceResult()
	{
		// X = lose
		if ( ForcedResult == 'X' )
		{
			if ( Opponent == RPSVal::Rock )
				Self = RPSVal::Scissors;
			else if ( Opponent == RPSVal::Paper )
				Self = RPSVal::Rock;
			else if ( Opponent == RPSVal::Scissors )
				Self = RPSVal::Paper;
		}

		// Y = draw
		else if ( ForcedResult == 'Y' )
		{
			Self = Opponent;
		}

		// Z = win
		else if ( ForcedResult == 'Z' )
		{
			if ( Opponent == RPSVal::Rock )
				Self = RPSVal::Paper;
			else if ( Opponent == RPSVal::Paper )
				Self = RPSVal::Scissors;
			else if ( Opponent == RPSVal::Scissors )
				Self = RPSVal::Rock;
		} 
	}

	char ForcedResult;
	RPSVal Opponent;
	RPSVal Self;
};

void ReadDay2Input( const std::string& Filename, std::vector<RPSMatch>& Matches )
{
	std::ifstream myfile;
	myfile.open( Filename );

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		RPSMatch NewMatch;
		NewMatch.SetOpponent( Line[0] );
		NewMatch.SetSelf( Line[Line.size() - 1] );
		NewMatch.ForcedResult = Line[Line.size() - 1];
		Matches.push_back( NewMatch );
	}

	myfile.close();
}

int Day2Part1( const std::string& Filename )
{
	std::vector<RPSMatch> Matches;
	ReadDay2Input( Filename, Matches );

	int Score = 0;
	for ( const RPSMatch& Match : Matches )
	{
		Score += Match.GetSelfResult();
	}

	return Score;
}

int Day2Part2( const std::string& Filename )
{
	std::vector<RPSMatch> Matches;
	ReadDay2Input( Filename, Matches );

	int Score = 0;
	for ( RPSMatch& Match : Matches )
	{
		Match.ForceResult();
		Score += Match.GetSelfResult();
	}

	return Score;
}

int Day3Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<char> Letters;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		if ( Line.size() <= 0 )
		{
			continue;
		}

		std::string Left, Right;
		Left = Line.substr( 0, Line.size() / 2 );
		Right = Line.substr( Line.size() / 2, Line.size() - 1 );

		bool bFoundLetter = false;
		for ( size_t Idx = 0; Idx < Left.size(); ++Idx )
		{
			if ( std::count( Right.begin(), Right.end(), Left[Idx] ) )
			{
				Letters.push_back( Left[Idx] );
				bFoundLetter = true;
				break;
			}
		}

		if ( !bFoundLetter )
			std::cout << "bad" << std::endl;
	}

	int OutScore = 0;
	const int ASCIILowerDiff = 96;
	const int ASCIIUpperDiff = 38;
	for ( char Letter : Letters )
	{
		int Diff = isupper( Letter ) ? ASCIIUpperDiff : ASCIILowerDiff;
		int Score = static_cast< int >( Letter ) - Diff;
		OutScore += Score;
	}

	myfile.close();

	return OutScore;
}

int Day3Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<char> Letters;
	while ( myfile.good() )
	{
		std::vector<std::string> Lines;

		char line[256];
		myfile.getline( line, 256 );
		Lines.push_back( std::string( line ) );
		myfile.getline( line, 256 );
		Lines.push_back( std::string( line ) );
		myfile.getline( line, 256 );
		Lines.push_back( std::string( line ) );

		std::vector<char> Candidates;
		for ( size_t Idx = 0; Idx < Lines[0].size(); ++Idx )
		{
			if ( std::count( Lines[1].begin(), Lines[1].end(), Lines[0][Idx] ) )
			{
				Candidates.push_back( Lines[0][Idx] );
			}
		}

		if ( Candidates.size() == 0 )
			std::cout << "bad" << std::endl;

		bool bFoundLetter = false;
		for ( size_t Idx = 0; Idx < Lines[2].size(); ++Idx )
		{
			if ( std::count( Candidates.begin(), Candidates.end(), Lines[2][Idx] ) )
			{
				bFoundLetter = true;
				Letters.push_back( Lines[2][Idx] );
				break;
			}
		}

		if ( !bFoundLetter )
			std::cout << "bad" << std::endl;
	}

	int OutScore = 0;
	const int ASCIILowerDiff = 96;
	const int ASCIIUpperDiff = 38;
	for ( char Letter : Letters )
	{
		int Diff = isupper( Letter ) ? ASCIIUpperDiff : ASCIILowerDiff;
		int Score = static_cast< int >( Letter ) - Diff;
		OutScore += Score;
	}

	myfile.close();

	return OutScore;
}

struct ElfAssignment
{
	ElfAssignment( const std::string& InString )
	{
		Populate( InString );
	}

	void Populate( const std::string& InString )
	{
		auto start = 0U;
		auto end = InString.find( '-' );
		StartID = stoi( InString.substr( start, end ) );
		EndID = stoi( InString.substr( end + 1, std::string::npos ) );
	}

	bool DoesContain( const ElfAssignment& Other ) const
	{
		return StartID <= Other.StartID && EndID >= Other.EndID;;
	}

	bool DoesOverlap( const ElfAssignment& Other ) const
	{
		return !( EndID < Other.StartID || Other.EndID < StartID ) || DoesContain( Other ) || Other.DoesContain( *this );
	}

	int StartID = 0;
	int EndID = 0;
};

int Day4Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int ContainedSum = 0;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		auto start = 0U;
		auto end = Line.find( ',' );
		ElfAssignment Elf1( Line.substr( start, end ) );
		ElfAssignment Elf2( Line.substr( end + 1, std::string::npos ) );

		if ( Elf1.DoesContain( Elf2 ) || Elf2.DoesContain( Elf1 ) )
		{
			++ContainedSum;
		}
	}

	myfile.close();

	return ContainedSum;
}

int Day4Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int OverlappedSum = 0;
	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		auto start = 0U;
		auto end = Line.find( ',' );
		ElfAssignment Elf1( Line.substr( start, end ) );
		ElfAssignment Elf2( Line.substr( end + 1, std::string::npos ) );

		if ( Elf1.DoesOverlap( Elf2 ) )
		{
			++OverlappedSum;
		}
	}

	myfile.close();

	return OverlappedSum;
}

struct LoadingDock
{
	std::vector<std::stack<char>> Stacks;

	std::string GetTopCrates() const
	{
		std::string CrateSum;
		for ( const std::stack<char>& Stack : Stacks )
		{
			CrateSum += Stack.top();
		}
		return CrateSum;
	}
};

void ReadDay5Line( const std::string& Line, int& OutSrc, int& OutDest, int& OutCt )
{
	//move 1 from 2 to 1
	std::string MutLine = Line.substr( 5, std::string::npos );
	auto start = 0U;
	auto end = Line.find( " ", 6 );
	OutCt = stoi( Line.substr( 5, end - 5 ) );

	start = end - 5;
	MutLine = Line.substr( end + 6, std::string::npos );
	end = MutLine.find( " " );
	OutSrc = stoi( MutLine.substr( 0, end ) );
	OutSrc--;

	start = end + 4;
	MutLine = MutLine.substr( start, std::string::npos );
	OutDest = stoi( MutLine );
	OutDest--;
}

std::string Day5Part1( const std::string& Filename, int NumDockLines, const LoadingDock& Input )
{
	LoadingDock MutDock = Input;

	std::ifstream myfile;
	myfile.open( Filename );

	for ( int Ct = 0; Ct < NumDockLines; ++Ct )
	{
		char line[256];
		myfile.getline( line, 256 );
	}

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		int Src, Dst, Ct;
		ReadDay5Line( Line, Src, Dst, Ct );

		for ( int Idx = 0; Idx < Ct; ++Idx )
		{
			char Item = MutDock.Stacks[Src].top();
			MutDock.Stacks[Src].pop();
			MutDock.Stacks[Dst].push( Item );
		}
	}

	myfile.close();

	return MutDock.GetTopCrates();
}

std::string Day5Part2( const std::string& Filename, int NumDockLines, const LoadingDock& Input )
{
	LoadingDock MutDock = Input;

	std::ifstream myfile;
	myfile.open( Filename );

	for ( int Ct = 0; Ct < NumDockLines; ++Ct )
	{
		char line[256];
		myfile.getline( line, 256 );
	}

	while ( myfile.good() )
	{
		char line[256];
		myfile.getline( line, 256 );
		std::string Line( line );

		int Src, Dst, Ct;
		ReadDay5Line( Line, Src, Dst, Ct );

		std::stack<char> Crane;
		for ( int Idx = 0; Idx < Ct; ++Idx )
		{
			Crane.push( MutDock.Stacks[Src].top() );
			MutDock.Stacks[Src].pop();
		}
		while ( Crane.size() > 0 )
		{
			MutDock.Stacks[Dst].push( Crane.top() );
			Crane.pop();
		}
	}

	myfile.close();

	return MutDock.GetTopCrates();
}

bool AreCharactersUnique( const std::string& InString )
{
	for ( char Curr : InString )
	{
		if ( std::count( InString.begin(), InString.end(), Curr ) > 1 )
		{
			return false;
		}
	}

	return true;
}

int Day6Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[2048];
		myfile.getline( line, 2048 );
		std::string Line( line );

		if ( Line.size() < 4 )
		{
			continue;
		}

		if ( Line[0] != Line[1]
			&& Line[0] != Line[2]
			&& Line[0] != Line[3]
			&& Line[1] != Line[2]
			&& Line[1] != Line[3]
			&& Line[2] != Line[3]
			)
		{
			Answer = 3;
			continue;
		}

		for ( size_t Idx = 4; Idx < Line.size(); ++Idx )
		{
			if ( AreCharactersUnique( Line.substr( Idx - 4, 4 ) ) )
			{
				Answer = Idx;
				break;
			}
		}
	}

	myfile.close();

	return Answer;
}

int Day6Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int Answer = 0;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		if ( Line.size() < 14 )
		{
			continue;
		}

		for ( size_t Idx = 14; Idx <= Line.size(); ++Idx )
		{
			if ( AreCharactersUnique( Line.substr( Idx - 14, 14 ) ) )
			{
				Answer = Idx;
				break;
			}
		}
	}

	myfile.close();

	return Answer;
}

void ReadDay7Line( const std::string& Line, bool& bIsCommand, std::string& First, std::string& Second )
{
	auto start = 0U;

	if ( Line.size() > 0 && Line[0] == '$' )
	{
		bIsCommand = true;
		start = 2;
	}
	else
	{
		bIsCommand = false;
	}

	auto end = Line.find( " ", start );
	First = Line.substr( start, end - start );
	Second = Line.substr( end + 1, std::string::npos );
}

struct ElfResource
{
	ElfResource( std::string& First, std::string& Second )
	{
		if ( First == "dir" )
		{
			bIsDir = true;
			ResourceName = Second;
		}
		else
		{
			ResourceName = Second;
			ResourceSize = stoi( First );
		}
	}

	~ElfResource()
	{
		for ( ElfResource* Sub : Resources )
		{
			if ( Sub )
			{
				delete Sub;
			}
		}
	}

	int CalcSize()
	{
		if ( !bIsDir )
		{
			return ResourceSize;
		}

		int SumResources = 0;
		for ( ElfResource* Curr : Resources )
		{
			SumResources += Curr->CalcSize();
		}
		ResourceSize = SumResources;
		return SumResources;
	}

	bool bIsDir = false;
	int ResourceSize = 0;
	std::string ResourceName;
	ElfResource* Parent = nullptr;
	std::vector<ElfResource*> Resources;
};

int SumLargeDirectories( const ElfResource* Root, int Threshold )
{
	int Sum = 0;
	if ( Root->bIsDir )
	{
		if ( Root->ResourceSize <= Threshold )
		{
			Sum += Root->ResourceSize;
		}

		for ( const ElfResource* Resource : Root->Resources )
		{
			Sum += SumLargeDirectories( Resource, Threshold );
		}
	}
	return Sum;
}

int FindClosestDirectories( const ElfResource* Root, int Threshold )
{
	int Closest = INT_MAX;
	if ( Root->bIsDir )
	{
		if ( Root->ResourceSize > Threshold )
		{
			Closest = Root->ResourceSize;
		}

		for ( const ElfResource* Resource : Root->Resources )
		{
			Closest = std::min( FindClosestDirectories( Resource, Threshold ), Closest );
		}
	}
	return Closest;
}

int Day7Part1( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::string DirLiteral = "dir";
	std::string RootName = "/";
	ElfResource* RootResource = new ElfResource( DirLiteral, RootName );
	ElfResource* CurrResource = RootResource;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		bool bIsCommand;
		std::string First, Second;
		ReadDay7Line( Line, bIsCommand, First, Second );

		if ( bIsCommand )
		{
			if ( First == "cd" )
			{
				if ( Second == "/" )
				{
					// Nav to root
					CurrResource = RootResource;
				}
				else if ( Second == ".." )
				{
					CurrResource = CurrResource->Parent;
				}
				else
				{
					// Nav to second
					for ( ElfResource* Curr : CurrResource->Resources )
					{
						if ( Curr && Curr->ResourceName == Second )
						{
							CurrResource = Curr;
							break;
						}
					}
				}
			}
		}
		else
		{
			ElfResource* NewResource = new ElfResource( First, Second );
			CurrResource->Resources.push_back( NewResource );
			NewResource->Parent = CurrResource;
		}
	}

	RootResource->CalcSize();
	int Output = SumLargeDirectories( RootResource, 100000 );

	delete RootResource;
	RootResource = nullptr;
	CurrResource = nullptr;

	myfile.close();

	return Output;
}

int Day7Part2( const std::string& Filename )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::string DirLiteral = "dir";
	std::string RootName = "/";
	ElfResource* RootResource = new ElfResource( DirLiteral, RootName );
	ElfResource* CurrResource = RootResource;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		bool bIsCommand;
		std::string First, Second;
		ReadDay7Line( Line, bIsCommand, First, Second );

		if ( bIsCommand )
		{
			if ( First == "cd" )
			{
				if ( Second == "/" )
				{
					// Nav to root
					CurrResource = RootResource;
				}
				else if ( Second == ".." )
				{
					CurrResource = CurrResource->Parent;
				}
				else
				{
					// Nav to second
					for ( ElfResource* Curr : CurrResource->Resources )
					{
						if ( Curr && Curr->ResourceName == Second )
						{
							CurrResource = Curr;
							break;
						}
					}
				}
			}
		}
		else
		{
			ElfResource* NewResource = new ElfResource( First, Second );
			CurrResource->Resources.push_back( NewResource );
			NewResource->Parent = CurrResource;
		}
	}

	RootResource->CalcSize();
	int SpaceAvailable = 70000000 - RootResource->ResourceSize;
	int Output = FindClosestDirectories( RootResource, 30000000 - SpaceAvailable );

	delete RootResource;
	RootResource = nullptr;
	CurrResource = nullptr;

	myfile.close();

	return Output;
}

struct Forest
{
	std::vector<std::vector<int>> TreeGrid;

	void Print() const
	{
		for ( const std::vector<int>& Row : TreeGrid )
		{
			for ( int Tree : Row )
			{
				std::cout << Tree << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	bool IsTreeVisible( int Row, int Col ) const
	{
		int TreeHeight = TreeGrid[Row][Col];
		int GridSize = TreeGrid.size();

		bool LeftVisible = true;
		for ( int RowLeft = 0; RowLeft < Row; ++RowLeft )
		{
			if ( TreeGrid[RowLeft][Col] >= TreeHeight )
			{
				LeftVisible = false;
				break;
			}
		}

		bool RightVisible = true;
		for ( int RowRight = Row + 1; RowRight < GridSize; ++RowRight )
		{
			if ( TreeGrid[RowRight][Col] >= TreeHeight )
			{
				RightVisible = false;
				break;
			}
		}

		bool UpVisible = true;
		for ( int ColUp = 0; ColUp < Col; ++ColUp )
		{
			if ( TreeGrid[Row][ColUp] >= TreeHeight )
			{
				UpVisible = false;
				break;
			}
		}

		bool DownVisible = true;
		for ( int ColDown = Col + 1; ColDown < GridSize; ++ColDown )
		{
			if ( TreeGrid[Row][ColDown] >= TreeHeight )
			{
				DownVisible = false;
				break;
			}
		}

		// We could stop after finding a true one of these, but who knows, maybe we'll need this for part 2
		return LeftVisible || RightVisible || UpVisible || DownVisible;
	}

	// Brute force babyyyyy
	int GetVisibleTreeCount() const
	{
		int GridSize = TreeGrid.size();

		// Don't need to check edges, just account for them up front
		int TreeCt = GridSize * 4 - 4;

		for ( int Row = 1; Row < GridSize - 1; ++Row )
		{
			for ( int Col = 1; Col < GridSize - 1; ++Col )
			{
				if ( IsTreeVisible( Row, Col ) )
				{
					++TreeCt;
				}
			}
		}

		return TreeCt;
	}

	int GetScenicScore( int Row, int Col ) const
	{
		int GridSize = TreeGrid.size();
		int TreeHeight = TreeGrid[Row][Col];

		int LeftScore = 0;
		for ( int RowLeft = Row - 1; RowLeft >= 0; --RowLeft )
		{
			++LeftScore;
			if ( TreeGrid[RowLeft][Col] >= TreeHeight )
			{
				break;
			}
		}

		int RightScore = 0;
		for ( int RowRight = Row + 1; RowRight < GridSize; ++RowRight )
		{
			++RightScore;
			if ( TreeGrid[RowRight][Col] >= TreeHeight )
			{
				break;
			}
		}

		int UpScore = 0;
		for ( int ColUp = Col - 1; ColUp >= 0; --ColUp )
		{
			++UpScore;
			if ( TreeGrid[Row][ColUp] >= TreeHeight )
			{
				break;
			}
		}

		int DownScore = 0;
		for ( int ColDown = Col + 1; ColDown < GridSize; ++ColDown )
		{
			++DownScore;
			if ( TreeGrid[Row][ColDown] >= TreeHeight )
			{
				break;
			}
		}

		return LeftScore * RightScore * UpScore * DownScore;
	}

	int GetBestScenicScore() const
	{
		int GridSize = TreeGrid.size();

		int BestScore = 0;

		for ( int Row = 1; Row < GridSize - 1; ++Row )
		{
			for ( int Col = 1; Col < GridSize - 1; ++Col )
			{
				BestScore = std::max( BestScore, GetScenicScore( Row, Col ) );
			}
		}

		return BestScore;
	}
};

void ReadDay8Input( const std::string& Filename, Forest& OutForest )
{
	std::ifstream myfile;
	myfile.open( Filename );

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		// I don't have to make these ints, chars would work just as well, but what are you gonna do, sue me?
		std::vector<int> NewRow;
		for ( char Entry : Line )
		{
			// support for 0 - 9 ONLY
			NewRow.push_back( Entry - '0' );
		}
		OutForest.TreeGrid.push_back( NewRow );
	}

	myfile.close();
}

int Day8Part1( const std::string& Filename )
{
	Forest SampleForest;
	ReadDay8Input( Filename, SampleForest );
	//SampleForest.Print();

	return SampleForest.GetVisibleTreeCount();
}

int Day8Part2( const std::string& Filename )
{
	Forest SampleForest;
	ReadDay8Input( Filename, SampleForest );

	return SampleForest.GetBestScenicScore();
}

struct IntVector2D
{
	IntVector2D( int InX = 0, int InY = 0 ) : X( InX ), Y( InY ) {}

	bool operator==( const IntVector2D& Other ) const { return X == Other.X && Y == Other.Y; }
	bool operator!=( const IntVector2D& Other ) const { return !(*this == Other); }
	IntVector2D operator+( const IntVector2D& Other ) const { return IntVector2D( X + Other.X, Y + Other.Y ); }
	IntVector2D operator-( const IntVector2D& Other ) const { return IntVector2D( X - Other.X, Y - Other.Y ); }
	IntVector2D operator*( const IntVector2D& Other ) const { return IntVector2D( X * Other.X, Y * Other.Y ); }
	IntVector2D operator*( int Scale ) const { return IntVector2D( X * Scale, Y * Scale ); }
	IntVector2D operator/( const IntVector2D& Other ) const { return IntVector2D( Other.X ? X / Other.X : 0, Other.Y ? Y / Other.Y : 0 ); }
	IntVector2D operator/( int Scale ) const { return IntVector2D( Scale ? X / Scale : 0, Scale ? Y / Scale : 0 ); }

	static IntVector2D Up;
	static IntVector2D Right;
	static IntVector2D Down;
	static IntVector2D Left;

	// Ew
	int Size() const { return (int)std::sqrtf( (float)(X * X + Y * Y )); }

	int X;
	int Y;
}; 

IntVector2D IntVector2D::Up		= IntVector2D(0, 1);
IntVector2D IntVector2D::Right	= IntVector2D( 1, 0 );
IntVector2D IntVector2D::Down	= IntVector2D( 0, -1 );
IntVector2D IntVector2D::Left	= IntVector2D( -1, 0 );
static int ManhattanDist( const IntVector2D& A, const IntVector2D& B )
{
	return std::abs( A.X - B.X ) + std::abs( A.Y - B.Y );
}

// Don't look at this it's not good.
inline bool operator<( const IntVector2D& lhs, const IntVector2D& rhs )
{
	return lhs.X != rhs.X ? lhs.X < rhs.X : lhs.Y < rhs.Y;
}

IntVector2D ReadDay9Line( const std::string& Line )
{
	IntVector2D OutVector;

	int Scale = stoi( Line.substr( 2 ) );
	char Dir = Line[0];
	if ( Dir == 'U' )
		OutVector.Y = Scale;
	else if ( Dir == 'D' )
		OutVector.Y = -Scale;
	else if ( Dir == 'L' )
		OutVector.X = -Scale;
	else if ( Dir == 'R' )
		OutVector.X = Scale;
	else
		std::cout << "This has gone bad: " << Line << std::endl;

	return OutVector;
}

int Day9Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );


	std::queue<IntVector2D> Instructions;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Instructions.push( ReadDay9Line( Line ) );
	}

	myfile.close();

	std::set<IntVector2D> VisitedLocations;
	IntVector2D HeadPos;
	IntVector2D TailPos;
	while ( Instructions.size() > 0 )
	{
		const IntVector2D& Instruction = Instructions.front();
		Instructions.pop();

		if ( bShouldPrint )
		{
			std::cout << "== " << Instruction.X << " " << Instruction.Y << " ==" << std::endl;
		}

		IntVector2D StepDir = Instruction / Instruction.Size();
		for ( int Ct = 0; Ct < Instruction.Size(); ++Ct )
		{
			HeadPos = HeadPos + StepDir;

			IntVector2D Dir = HeadPos - TailPos;
			bool bIsXTouching = std::abs( HeadPos.X - TailPos.X ) <= 1;
			bool bIsYTouching = std::abs( HeadPos.Y - TailPos.Y ) <= 1;

			if ( HeadPos.X == TailPos.X && !bIsYTouching )
			{
				TailPos.Y += Dir.Y / std::abs(Dir.Y);
			}
			else if ( HeadPos.Y == TailPos.Y && !bIsXTouching )
			{
				TailPos.X += Dir.X / std::abs(Dir.X);
			}
			else if ( !bIsYTouching || !bIsXTouching )
			{
				TailPos.X += Dir.X ? Dir.X / std::abs( Dir.X ) : 0;
				TailPos.Y += Dir.Y ? Dir.Y / std::abs( Dir.Y ) : 0;
			}
			/*
			else
			{
				if ( !bIsXTouching )
					TailPos.X += Dir.X / Dir.X;
				if ( !bIsYTouching )
					TailPos.Y += Dir.Y / Dir.Y;
			}
			//*/

			VisitedLocations.insert( TailPos );

			if ( bShouldPrint )
			{
				for ( int Row = 4; Row >= 0; --Row )
				{
					for ( int Col = 0; Col < 6; ++Col )
					{
						IntVector2D Curr( Col, Row );
						char Selected = '.';
						if ( VisitedLocations.count( IntVector2D( Col, Row ) ) )
						{
							Selected = '#';
						}

						if ( Curr == TailPos )
						{
							Selected = 'T';
						}

						if ( Curr == HeadPos )
						{
							Selected = 'H';
						}

						std::cout << Selected;
					}

					std::cout << std::endl;
				}

				std::cout << std::endl;
			}
			}

		/*

		HeadPos = HeadPos + Instruction;

		IntVector2D Dir = HeadPos - TailPos;
		if ( Dir.X != 0 )
		{
			float Num = ( float )(std::abs( Dir.X ) - 1);
			float Denom = ( float )Dir.X;
			Dir.X = int( (float)Dir.X * Num / Denom );
		}
		if ( Dir.Y != 0 )
		{
			float Num = ( float )( std::abs( Dir.Y ) - 1 );
			float Denom = ( float )Dir.Y;
			Dir.Y = int( ( float )Dir.Y * Num / Denom );
		}
		//TailPos.X = std::min( std::max(TailPos.X, -1), 1 );
		//TailPos.Y = std::min( std::max(TailPos.Y, -1), 1 );

		TailPos = TailPos + Dir;
		//*/
	}

	return VisitedLocations.size();
}

void UpdateRopeSection( const IntVector2D& HeadPos, IntVector2D& TailPos )
{
	IntVector2D Dir = HeadPos - TailPos;
	bool bIsXTouching = std::abs( HeadPos.X - TailPos.X ) <= 1;
	bool bIsYTouching = std::abs( HeadPos.Y - TailPos.Y ) <= 1;

	if ( HeadPos.X == TailPos.X && !bIsYTouching )
	{
		TailPos.Y += Dir.Y / std::abs( Dir.Y );
	}
	else if ( HeadPos.Y == TailPos.Y && !bIsXTouching )
	{
		TailPos.X += Dir.X / std::abs( Dir.X );
	}
	else if ( !bIsYTouching || !bIsXTouching )
	{
		TailPos.X += Dir.X ? Dir.X / std::abs( Dir.X ) : 0;
		TailPos.Y += Dir.Y ? Dir.Y / std::abs( Dir.Y ) : 0;
	}
}

int Day9Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );


	std::queue<IntVector2D> Instructions;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Instructions.push( ReadDay9Line( Line ) );
	}

	myfile.close();

	std::set<IntVector2D> VisitedLocations;
	std::vector<IntVector2D> KnotList(10, IntVector2D());

	while ( Instructions.size() > 0 )
	{
		const IntVector2D& Instruction = Instructions.front();
		Instructions.pop();

		if ( bShouldPrint )
		{
			std::cout << "== " << Instruction.X << " " << Instruction.Y << " ==" << std::endl;
		}

		IntVector2D StepDir = Instruction / Instruction.Size();
		for ( int Ct = 0; Ct < Instruction.Size(); ++Ct )
		{

			KnotList[0] = KnotList[0] + StepDir;

			for ( size_t Idx = 1; Idx < KnotList.size(); ++Idx )
			{
				UpdateRopeSection( KnotList[Idx - 1], KnotList[Idx] );
			}

			VisitedLocations.insert( KnotList[KnotList.size() - 1] );

			if ( bShouldPrint )
			{
				for ( int Row = 4; Row >= 0; --Row )
				{
					for ( int Col = 0; Col < 6; ++Col )
					{
						IntVector2D Curr( Col, Row );
						char Selected = '.';
						if ( VisitedLocations.count( IntVector2D( Col, Row ) ) )
						{
							Selected = '#';
						}

						for ( int Idx = KnotList.size() - 1; Idx >= 0; --Idx )
						{

							if ( Curr == KnotList[Idx] )
							{
								Selected = '0' + (char)Idx;

								if ( Idx == (int)KnotList.size() - 1 )
								{
									Selected = 'T';
								}

								if ( Idx == 0 )
								{
									Selected = 'H';
								}
							}
						}

						std::cout << Selected;
					}

					std::cout << std::endl;
				}

				std::cout << std::endl;
			}
		}
	}

	return VisitedLocations.size();
}

struct Day10CPU
{
	void ExecuteInstruction( const std::string& Instruction )
	{
		auto SplitIdx = Instruction.find( ' ' );
		if ( SplitIdx != std::string::npos )
		{
			std::string SplitInstruction = Instruction.substr( 0, SplitIdx );
			if ( SplitInstruction == "addx" )
			{
				int XVal = stoi( Instruction.substr( SplitIdx + 1 ) );
				XRegister += XVal;
				ClockCount += 2;
			}
		}
		else
		{
			if ( Instruction == "noop" )
			{
				++ClockCount;
			}
		}
	}

	int ClockCount = 0;
	int XRegister = 1;
};

int GetXRegisterAtTick( const std::vector<std::string>& Instructions, int ClockValue )
{
	Day10CPU Cpu;
	int PrevXVal = 0;
	int OutVal = 0;
	for ( const std::string& Instruction : Instructions )
	{
		Cpu.ExecuteInstruction( Instruction );
		if ( Cpu.ClockCount > ClockValue )
		{
			OutVal = PrevXVal;
			break;
		}
		else if ( Cpu.ClockCount == ClockValue )
		{
			OutVal = Cpu.XRegister;
			break;
		}
		else
		{
			PrevXVal = Cpu.XRegister;
		}
	}

	return OutVal;
}

int CalculateFrequency( const std::vector<std::string>& Instructions, int ClockValue )
{
	Day10CPU Cpu;
	int PrevXVal = 0;
	int OutVal = 0;
	for ( const std::string& Instruction : Instructions )
	{
		Cpu.ExecuteInstruction( Instruction );
		if ( Cpu.ClockCount >= ClockValue )
		{
			OutVal = PrevXVal;
			break;
		}
		{
			PrevXVal = Cpu.XRegister;
		}
	}

	return OutVal * ClockValue;
}

int Day10Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::string> InstructionStack;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		InstructionStack.push_back( Line );
	}

	myfile.close();

	int FrequencySum = 0;

	//20th, 60th, 100th, 140th, 180th, and 220th
	FrequencySum += CalculateFrequency( InstructionStack, 20 );
	FrequencySum += CalculateFrequency( InstructionStack, 60 );
	FrequencySum += CalculateFrequency( InstructionStack, 100 );
	FrequencySum += CalculateFrequency( InstructionStack, 140 );
	FrequencySum += CalculateFrequency( InstructionStack, 180 );
	FrequencySum += CalculateFrequency( InstructionStack, 220 );

	return FrequencySum;
}

int Day10Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::string> InstructionStack;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		InstructionStack.push_back( Line );
	}

	myfile.close();

	// Could ABSOLUTELY do this better. If I had any incentive to do so, the CPU would store it's instructions and we'd query it every tick. Maybe I'll switch to that, but probably not!
	int RowCount = 6;
	int RowLength = 40;
	for ( int Row = 0; Row < RowCount; ++Row )
	{
		for ( int Col = 0; Col < RowLength; ++Col )
		{
			int SpriteLoc = GetXRegisterAtTick( InstructionStack, Row * RowLength + Col );
			if ( std::abs( SpriteLoc - Col ) <= 1 )
			{
				std::cout << '#';
			}
			else
			{
				std::cout << '.';
			}
		}

		std::cout << std::endl;
	}

	return 0;
}

struct Monkey
{
	std::vector<unsigned long long> HeldItems;
	unsigned long InspectionCount = 0;

	std::function<unsigned long long( unsigned long long )> Operation;

	int Divisor;
	int TrueDest;
	int FalseDest;

	void HandleItems1( std::vector<Monkey>& Monkeys )
	{
		for ( unsigned long long Item : HeldItems )
		{
			++InspectionCount;

			Item = Operation( Item );

			Item /= 3;

			int DestMonkey = Test( Item );

			Monkeys[DestMonkey].HeldItems.push_back( Item );
		}

		HeldItems.clear();
	}

	void HandleItems2( std::vector<Monkey>& Monkeys, unsigned long long MaxVal )
	{
		for ( unsigned long long Item : HeldItems )
		{
			++InspectionCount;

			Item = Operation( Item );

			Item %= MaxVal;

			int DestMonkey = Test(Item);

			Monkeys[DestMonkey].HeldItems.push_back( Item );
		}

		HeldItems.clear();
	}

	int Test( unsigned long long& Old )
	{
		if ( Old % Divisor == 0 )
		{
			return TrueDest;
		}

		return FalseDest;
	}

	void Print() const
	{
		for ( unsigned long long Item : HeldItems )
		{
			std::cout << Item << " ";
		}
		std::cout << std::endl;
	}
};

int Day11Part1( std::vector<Monkey>& InMonkeys, bool bShouldPrint = false )
{
	int NumRounds = 20;

	for ( int Round = 0; Round < NumRounds; ++Round )
	{
		for ( Monkey& Curr : InMonkeys )
		{
			Curr.HandleItems1( InMonkeys );
		}

		if ( bShouldPrint )
		{
			for ( Monkey& Curr : InMonkeys )
			{
				Curr.Print();
			}
		}
	}

	std::vector<unsigned long> InspectCounts;
	for ( const Monkey& Curr : InMonkeys )
	{
		InspectCounts.push_back( Curr.InspectionCount );
	}

	std::sort( InspectCounts.rbegin(), InspectCounts.rend() );

	return InspectCounts[0] * InspectCounts[1];
}

unsigned long long Day11Part2( std::vector<Monkey>& InMonkeys, bool bShouldPrint = false )
{
	int NumRounds = 10000;
	
	unsigned long long MaxVal = 1;
	for ( const Monkey& Curr : InMonkeys )
	{
		MaxVal *= Curr.Divisor;
	}

	for ( int Round = 0; Round < NumRounds; ++Round )
	{
		for ( Monkey& Curr : InMonkeys )
		{
			Curr.HandleItems2( InMonkeys, MaxVal );
		}
	}

	std::vector<unsigned long long> InspectCounts;
	for ( const Monkey& Curr : InMonkeys )
	{
		InspectCounts.push_back( Curr.InspectionCount );
	}

	if ( bShouldPrint )
	{
		for ( size_t Idx = 0; Idx < InMonkeys.size(); ++Idx )
		{
			const Monkey& Curr = InMonkeys[Idx];
			std::cout << "Monkey " << Idx << ": " << Curr.InspectionCount << std::endl;
		}
	}

	std::sort( InspectCounts.rbegin(), InspectCounts.rend() );

	return InspectCounts[0] * InspectCounts[1];
}

struct HeightmapEntry
{
	HeightmapEntry( char InHeight = ' ', const IntVector2D& InPos = IntVector2D(-1, -1)) : Height(InHeight), Pos(InPos) {}

	char Height;
	IntVector2D Pos;
	IntVector2D Prev = IntVector2D(-1, -1);

	bool WasVisited() const { return Prev.X >= 0 && Prev.Y >= 0; }
	static char GetCharFromDir( const IntVector2D& Dir )
	{
		if ( Dir == IntVector2D::Left )
		{
			return '^';
		}
		else if ( Dir == IntVector2D::Up )
		{
			return '>';
		}
		else if ( Dir == IntVector2D::Right )
		{
			return 'v';
		}
		else if ( Dir == IntVector2D::Down )
		{
			return '<';
		}

		return '.';
	}
	char GetDirFromPrev() const 
	{
		return GetCharFromDir( Pos - Prev );
	}
};

struct Heightmap
{
	std::vector<std::vector<HeightmapEntry>> Map;
	IntVector2D StartPos;
	IntVector2D EndPos;

	std::vector<IntVector2D> Path;

	void AddMapLine(const std::string& InLine)
	{
		int CurrRow = Map.size();
		std::vector<HeightmapEntry> Entries;
		for ( size_t Col = 0; Col < InLine.size(); ++Col )
		{
			char InHeight = InLine[Col];
			if ( InHeight == 'S' )
			{
				InHeight = 'a';
				StartPos = IntVector2D( CurrRow, Col );
			}
			else if ( InHeight == 'E' )
			{
				InHeight = 'z';
				EndPos = IntVector2D( CurrRow, Col );
			}

			Entries.push_back( HeightmapEntry( InHeight, IntVector2D( CurrRow, Col ) ) );
		}

		Map.push_back( Entries );
	}

	HeightmapEntry& GetEntry( const IntVector2D& InLoc )
	{
		return Map[InLoc.X][InLoc.Y];
	}

	const HeightmapEntry& GetEntry( const IntVector2D& InLoc ) const
	{
		return Map[InLoc.X][InLoc.Y];
	}

	bool IsValid( const IntVector2D& InVector ) const
	{
		return InVector.X >= 0 && InVector.Y >= 0 && InVector.X < static_cast< int >( Map.size() ) && Map.size() > 0 && InVector.Y < static_cast< int >( Map[0].size() );
	}

	void AddValidNeighbors( const IntVector2D& InVec, std::queue<IntVector2D>& OutLocs )
	{
		std::vector<IntVector2D> Neighbors{ IntVector2D( InVec.X + 1, InVec.Y ), IntVector2D( InVec.X - 1, InVec.Y ), IntVector2D( InVec.X, InVec.Y + 1 ), IntVector2D( InVec.X, InVec.Y - 1 ) };

		for ( const IntVector2D& Neighbor : Neighbors )
		{
			if ( IsValid( Neighbor ) && !GetEntry( Neighbor ).WasVisited() )
			{
				if ( GetEntry( Neighbor ).Height - GetEntry( InVec ).Height <= 1 )
				{
					GetEntry( Neighbor ).Prev = InVec;
					OutLocs.push( Neighbor );
				}
			}
		}
	}

	void AddValidNeighborsRev( const IntVector2D& InVec, std::queue<IntVector2D>& OutLocs )
	{
		std::vector<IntVector2D> Neighbors{ IntVector2D( InVec.X + 1, InVec.Y ), IntVector2D( InVec.X - 1, InVec.Y ), IntVector2D( InVec.X, InVec.Y + 1 ), IntVector2D( InVec.X, InVec.Y - 1 ) };

		for ( const IntVector2D& Neighbor : Neighbors )
		{
			if ( IsValid( Neighbor ) && !GetEntry( Neighbor ).WasVisited() )
			{
				if ( GetEntry( InVec ).Height - GetEntry( Neighbor ).Height <= 1 )
				{
					GetEntry( Neighbor ).Prev = InVec;
					OutLocs.push( Neighbor );
				}
			}
		}
	}

	void SolvePath()
	{
		std::queue<IntVector2D> ToVisit;
		ToVisit.push( StartPos );
		GetEntry( StartPos ).Prev = StartPos;

		IntVector2D CurrEntry;
		while ( CurrEntry != EndPos && ToVisit.size() > 0 )
		{
			CurrEntry = ToVisit.front();
			ToVisit.pop();

			AddValidNeighbors( CurrEntry, ToVisit );
		}

		if ( CurrEntry != EndPos )
		{
			std::cout << "Failed to find path." << std::endl;
		}

		HeightmapEntry* CurrMapEntry = &GetEntry( EndPos );
		while ( CurrMapEntry && CurrMapEntry->Pos != StartPos && CurrMapEntry->WasVisited() )
		{
			Path.push_back( CurrMapEntry->Pos );
			CurrMapEntry = &GetEntry( CurrMapEntry->Prev );
		}
	}

	void SolvePathToFirstA()
	{
		std::queue<IntVector2D> ToVisit;
		ToVisit.push( EndPos );
		GetEntry( EndPos ).Prev = StartPos;

		IntVector2D CurrEntry = EndPos;
		while ( GetEntry(CurrEntry).Height != 'a' && ToVisit.size() > 0 )
		{
			CurrEntry = ToVisit.front();
			ToVisit.pop();

			AddValidNeighborsRev( CurrEntry, ToVisit );
		}

		if ( GetEntry( CurrEntry ).Height != 'a' )
		{
			std::cout << "Failed to find path." << std::endl;
		}

		HeightmapEntry* CurrMapEntry = &GetEntry( CurrEntry );
		while ( CurrMapEntry && CurrMapEntry->Pos != EndPos && CurrMapEntry->WasVisited() )
		{
			Path.push_back( CurrMapEntry->Pos );
			CurrMapEntry = &GetEntry( CurrMapEntry->Prev );
		}
	}

	void Print() const
	{
		for ( auto& Line : Map )
		{
			for ( auto& Entry : Line )
			{
				std::cout << Entry.Height;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int GetPathLen() const { return Path.size(); }

	void PrintPath() const
	{
		std::vector<std::vector<char>> PathData;
		const size_t RowCt = Map.size();
		const size_t ColCt = Map[0].size();
		for ( size_t Row = 0; Row < RowCt; ++Row )
		{
			std::vector<char> NewRow;
			for ( size_t Col = 0; Col < ColCt; ++Col )
			{
				NewRow.push_back( '.' );
			}
			PathData.push_back( NewRow );
		}

		IntVector2D CurrPathStep = EndPos;
		PathData[CurrPathStep.X][CurrPathStep.Y] = 'E'; 

		const HeightmapEntry& InitialStep = GetEntry( CurrPathStep );
		if ( InitialStep.WasVisited() )
		{
			PathData[InitialStep.Prev.X][InitialStep.Prev.Y] = InitialStep.GetDirFromPrev();
		}

		do
		{
			const HeightmapEntry& PrevStep = GetEntry( CurrPathStep );
			if ( !PrevStep.WasVisited() )
			{
				break;
			}
			const HeightmapEntry& CurrStep = GetEntry( PrevStep.Prev );
			if ( !CurrStep.WasVisited() )
			{
				break;
			}
			CurrPathStep = CurrStep.Pos;
			PathData[CurrStep.Prev.X][CurrStep.Prev.Y] = CurrStep.GetDirFromPrev();
		} while ( GetEntry(CurrPathStep).WasVisited() && !( GetEntry( CurrPathStep ).Prev == StartPos ) );

		for ( const std::vector<char>& Row : PathData )
		{
			for ( char Entry : Row )
			{
				std::cout << Entry;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void PrintPrevs() const
	{
		std::vector<std::vector<char>> PathData;
		const size_t RowCt = Map.size();
		const size_t ColCt = Map[0].size();
		for ( size_t Row = 0; Row < RowCt; ++Row )
		{
			std::vector<char> NewRow;
			for ( size_t Col = 0; Col < ColCt; ++Col )
			{
				NewRow.push_back( '.' );
			}
			PathData.push_back( NewRow );
		}

		for ( const std::vector<HeightmapEntry>& Row : Map )
		{
			for ( const HeightmapEntry& Entry : Row )
			{
				if ( Entry.WasVisited() )
				{
					PathData[Entry.Prev.X][Entry.Prev.Y] = Entry.GetDirFromPrev();
				}
			}
		}

		PathData[EndPos.X][EndPos.Y] = 'E';
		PathData[StartPos.X][StartPos.Y] = 'S';

		for ( const std::vector<char>& Row : PathData )
		{
			for ( char Entry : Row )
			{
				std::cout << Entry;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

int Day12Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	Heightmap Map;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Map.AddMapLine( Line );
	}

	myfile.close();

	if ( bShouldPrint )
	{
		Map.Print();
	}

	Map.SolvePath();

	if ( bShouldPrint )
	{
		Map.PrintPath();
		Map.PrintPrevs();
	}

	return Map.GetPathLen();
}

int Day12Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	Heightmap Map;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Map.AddMapLine( Line );
	}

	myfile.close();

	if ( bShouldPrint )
	{
		// Not Supported
		//Map.Print();
	}

	Map.SolvePathToFirstA();

	if ( bShouldPrint )
	{
		// Not Supported
		//Map.PrintPath();
		//Map.PrintPrevs();
	}

	return Map.GetPathLen();
}

std::string BreakList( const std::string& Input )
{
	return Input.substr( 1, Input.size() - 2 );
}

// Returns true if should continue
bool CompareInts( int Left, int Right, bool& OutResult )
{
	OutResult = Left < Right;
	return Left == Right;
}

bool IsList( const std::string& InLine )
{
	return InLine.size() > 0 && InLine[0] == '[';
}

std::string GetFirstElement( const std::string& InString )
{
	int ScopeDepth = 0;
	for ( size_t Idx = 0; Idx < InString.size(); ++Idx )
	{
		char Curr = InString[Idx];
		if ( Curr == ',' && ScopeDepth == 0 )
		{
			return InString.substr( 0, Idx );
		}

		if ( Curr == '[' )
		{
			++ScopeDepth;
		}
		else if ( Curr == ']' )
		{
			--ScopeDepth;
		}
	}

	return InString;
}

bool ArePacketsInOrder( const std::string& Left, const std::string& Right, bool& bOutResult )
{
	std::string LeftElems = Left;
	std::string RightElems = Right;

	while ( true )
	{
		// Get the next element
		std::string LeftElem = GetFirstElement( LeftElems );
		std::string RightElem = GetFirstElement( RightElems );

		// If left runs out first, we're in order
		if ( LeftElem.size() == 0 && RightElem.size() == 0 )
		{
			bOutResult = true;
			return true;
		}
		else if ( LeftElem.size() == 0 )
		{
			bOutResult = true;
			return false;
		}
		else if ( RightElem.size() == 0 )
		{
			bOutResult = false;
			return false;
		}

		// Process that element!
		bool bLeftIsList = IsList( LeftElem );
		bool bRightIsList = IsList( RightElem );

		if ( bLeftIsList && bRightIsList )
		{
			if ( !ArePacketsInOrder( BreakList( LeftElem ), BreakList( RightElem ), bOutResult ) )
			{
				return false;
			}
		}
		else if ( bLeftIsList == bRightIsList )
		{
			if ( !CompareInts( stoi( LeftElem ), stoi( RightElem ), bOutResult ) )
			{
				return false;
			}
		}
		else
		{
			std::string ListLeft = bLeftIsList ? LeftElem : std::string( '[' + LeftElem + ']' );
			std::string ListRight = bRightIsList ? RightElem : std::string( '[' + RightElem + ']' );
			if ( !ArePacketsInOrder( ListLeft, ListRight, bOutResult ) )
			{
				return false;
			}
		}

		size_t LeftIdx = LeftElems.find( ',' );
		size_t RightIdx = RightElems.find( ',' );
		LeftElems = LeftIdx == std::string::npos ? "" : LeftElems.substr( LeftIdx + 1 );
		RightElems = RightIdx == std::string::npos ? "" : RightElems.substr( RightIdx + 1 );
	}
}

int Day13Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	int CurrIdx = 1;
	int SumOrderedPairs = 0;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Left( line );
		myfile.getline( line, 4096 );
		std::string Right( line );

		bool bResult = false;
		ArePacketsInOrder( Left, Right, bResult );
		if ( bResult )
		{
			SumOrderedPairs += CurrIdx;
		}

		++CurrIdx;


		if ( !myfile.good() )
		{
			break;
		}

		// Clear the empty line
		myfile.getline( line, 4096 );
	}

	myfile.close();

	return SumOrderedPairs;
}

struct DistressPacket
{
	DistressPacket( const std::string& InString ) : Packet( InString ) {}

	bool operator<( const DistressPacket& Other ) const
	{
		bool bOutput = false;
		ArePacketsInOrder( this->Packet, Other.Packet, bOutput );
		return bOutput;
	}

	std::string Packet;
};

int Day13Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<DistressPacket> Packets;
	Packets.push_back( DistressPacket( "[[2]]"));
	Packets.push_back( DistressPacket( "[[6]]"));
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		if ( Line.size() > 0 )
		{
			Packets.push_back( DistressPacket( Line ) );
		}
	}

	myfile.close();

	std::sort( Packets.begin(), Packets.end() );

	int Idx0 = 0, Idx1 = 0;
	int Ct = 1;
	for ( const DistressPacket& Packet : Packets )
	{
		if ( Packet.Packet == "[[2]]" )
		{
			Idx0 = Ct;
		}
		else if ( Packet.Packet == "[[6]]" )
		{
			Idx1 = Ct;
		}

		if ( bShouldPrint )
		{
			std::cout << Packet.Packet << std::endl;
		}

		++Ct;
	}

	return Idx0 * Idx1;
}

struct CaveSliceSim
{
	CaveSliceSim( int MinWidth, int MaxWidth, int InHeight, bool bUseGround = false ) : Width(MaxWidth - MinWidth + 1), WidthOffset(MinWidth), Height(InHeight + 1), bHasGround(bUseGround)
	{
		if ( bUseGround )
		{
			Width += Height * 2;
			WidthOffset -= Height;
		}

		for ( int Row = 0; Row < Height; ++Row )
		{
			std::vector<char> RowStr;
			for (int Col = 0; Col < Width; ++Col )
			{
				RowStr.push_back( '.' );
			}
			Grid.push_back( RowStr );
		}

		if ( bUseGround )
		{
			std::vector<char> RowStr;
			for ( int Col = 0; Col < Width; ++Col )
			{
				RowStr.push_back( '.' );
			}
			Grid.push_back( RowStr );

			std::vector<char> FullStr;
			for ( int Col = 0; Col < Width; ++Col )
			{
				FullStr.push_back( '#' );
			}
			Grid.push_back( FullStr );
		}
	}

	void AddRockLine( const std::vector<IntVector2D>& Line )
	{
		for ( size_t Idx = 1; Idx < Line.size(); ++Idx )
		{
			IntVector2D Start = Line[Idx - 1];
			IntVector2D End = Line[Idx];

			IntVector2D Dir = End - Start;

			// Dumb Normal
			int XSign = Dir.X > 0 ? 1 : -1;
			int YSign = Dir.Y > 0 ? 1 : -1;
			Dir = Dir / Dir;
			Dir.X *= XSign;
			Dir.Y *= YSign;

			GetGridElement( Start.X, Start.Y + 1 ) = '#';
			while ( Start != End )
			{
				Start = Start + Dir;
				GetGridElement(Start.X, Start.Y + 1) = '#';
			}
		}
	}

	bool TickSim()
	{
		if ( CurrSandPos == IntVector2D( -1, -1 ) )
		{
			CurrSandPos = IntVector2D( 500, 1 );
			
			if ( GetGridElement( CurrSandPos ) == 'o' )
			{
				return false;
			}

			GetGridElement( CurrSandPos ) = '+';
			++SandCt;
		}
		else
		{
			IntVector2D NextSandPos = CurrSandPos;
			++NextSandPos.Y;

			if ( GetGridElement( NextSandPos ) == '.' )
			{
				// Nothing to do here, skip to the end!
			}
			else if ( !IsValidGridElement( NextSandPos.X - 1, NextSandPos.Y ) )
			{
				--SandCt;
				return false;
			}
			else if ( GetGridElement( NextSandPos.X - 1, NextSandPos.Y ) == '.' )
			{
				--NextSandPos.X;
			}
			else if ( !IsValidGridElement( NextSandPos.X + 1, NextSandPos.Y ) )
			{
				--SandCt;
				return false;
			}
			else if ( GetGridElement( NextSandPos.X + 1, NextSandPos.Y ) == '.' )
			{
				++NextSandPos.X;
			}
			else
			{
				GetGridElement( CurrSandPos ) = 'o';
				CurrSandPos = IntVector2D( -1, -1 );
				return true;
			}

			GetGridElement( CurrSandPos ) = '.';
			GetGridElement( NextSandPos ) = '+';
			CurrSandPos = NextSandPos;

			if ( !bHasGround && CurrSandPos.Y == Height )
			{
				return false;
			}
		}

		return true;
	}

	void Print() const
	{
		int Ct = 0;
		for ( const std::vector<char>& Row : Grid )
		{
			std::cout << Ct <<  " ";
			if ( Ct < 10 )
			{
				std::cout << " ";
			}

			for ( char Entry : Row )
			{
				std::cout << Entry;
			}
			std::cout << std::endl;
			++Ct;
		}
		std::cout << std::endl;
	}

	char& GetGridElement( const IntVector2D& InPos )
	{
		return GetGridElement( InPos.X, InPos.Y );
	}

	char& GetGridElement( int RawX, int Y )
	{
		return Grid[Y - 1][RawX - WidthOffset];
	}

	bool IsValidGridElement( const IntVector2D& InPos ) const
	{
		return IsValidGridElement( InPos.X, InPos.Y );
	}

	bool IsValidGridElement( int RawX, int Y ) const
	{
		int NewX = Y - 1;
		int NewY = RawX - WidthOffset;
		return NewX >= 0 && NewX < ( int )Grid.size() && NewY >= 0 && NewY < ( int )Grid[0].size();
	}

	std::vector<std::vector<char>> Grid;
	int Width;
	int WidthOffset;
	int Height;
	bool bHasGround;

	IntVector2D CurrSandPos = IntVector2D( -1, -1 );
	int SandCt = 0;
};

std::vector<IntVector2D> ReadDay14Line( const std::string& InLine )
{
	std::vector<IntVector2D> Points;
	auto Start = 0U;
	auto End = 0U;

	do
	{
		End = InLine.find( " -> ", Start );

		std::string Instruction = InLine.substr( Start, End - Start );

		Start = End + 4;

		// Don't ask me about this scope I don't wanna talk about it
		{
			size_t EndInd = Instruction.find( "," );
			Points.push_back( IntVector2D( stoi( Instruction.substr( 0, EndInd ) ), stoi( Instruction.substr( EndInd + 1 ) ) ) );
		}

	} while ( End != std::string::npos );

	return Points;
}

void GetWidthDimensions( const std::vector<std::vector<IntVector2D>>& Points, int& OutMinWidth, int& OutMaxWidth, int& OutHeight )
{
	OutMinWidth = INT_MAX;
	OutMaxWidth = INT_MIN;
	OutHeight = 0;

	for ( const std::vector<IntVector2D>& Row : Points )
	{
		for ( const IntVector2D& Point : Row )
		{
			if ( OutMinWidth > Point.X )
			{
				OutMinWidth = Point.X;
			}
			else if ( OutMaxWidth < Point.X )
			{
				OutMaxWidth = Point.X;
			}

			if ( OutHeight < Point.Y )
			{
				OutHeight = Point.Y;
			}
		}
	}
}

int Day14Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::vector<IntVector2D>> RockLines;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		RockLines.push_back( ReadDay14Line( Line ) );
	}

	myfile.close();

	int MinWidth, MaxWidth, Height;
	GetWidthDimensions( RockLines, MinWidth, MaxWidth, Height );

	CaveSliceSim Sim( MinWidth, MaxWidth, Height );
	if ( bShouldPrint )
		Sim.Print();

	for ( const std::vector<IntVector2D>& Line : RockLines )
	{
		Sim.AddRockLine( Line );
	}
	if ( bShouldPrint )
		Sim.Print();

	while ( Sim.TickSim() )
	{
		if ( bShouldPrint )
			Sim.Print();
	}

	return Sim.SandCt;
}

int Day14Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::vector<IntVector2D>> RockLines;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		RockLines.push_back( ReadDay14Line( Line ) );
	}

	myfile.close();

	int MinWidth, MaxWidth, Height;
	GetWidthDimensions( RockLines, MinWidth, MaxWidth, Height );

	CaveSliceSim Sim( MinWidth, MaxWidth, Height, true );
	if ( bShouldPrint )
		Sim.Print();

	for ( const std::vector<IntVector2D>& Line : RockLines )
	{
		Sim.AddRockLine( Line );
	}
	if ( bShouldPrint )
		Sim.Print();

	while ( Sim.TickSim() )
	{
		if ( bShouldPrint )
			Sim.Print();
	}

	return Sim.SandCt;
}

bool IsWithinRange( const IntVector2D& Pos, const IntVector2D& Other, int Dist )
{
	return ManhattanDist( Pos, Other ) <= Dist;
}

struct Sensor
{
	void Init( const std::string& InLine )
	{
		const static size_t DistToXVal = 12U;
		const static size_t DistToYVal = 4U;
		const static size_t DistToBeaconXVal = 25U;
		const static size_t DistToBeaconYVal = 4U;

		size_t Start = DistToXVal;
		size_t End = InLine.find( ",", Start );
		Pos.X = stoi( InLine.substr( Start, End - Start ) );
		
		Start = End + DistToYVal;
		End = InLine.find( ":", Start );
		Pos.Y = stoi( InLine.substr( Start, End - Start ) );

		Start = End + DistToBeaconXVal;
		End = InLine.find( ",", Start );
		ClosestBeaconPos.X = stoi( InLine.substr( Start, End - Start ) );

		Start = End + DistToBeaconYVal;
		End = InLine.find( ":", Start );
		ClosestBeaconPos.Y = stoi( InLine.substr( Start, End - Start ) );

		DistToBeacon = ManhattanDist(Pos, ClosestBeaconPos);
	}

	IntVector2D Pos;
	IntVector2D ClosestBeaconPos;
	int DistToBeacon = 0;
};

struct CaveSystem
{
	CaveSystem( int InMinX, int InMaxX, int InMinY, int InMaxY ) : ColOffset(InMinX), RowOffset(InMinY)
	{
		int Width = InMaxX - InMinX;
		int Height = InMaxY - InMinY;

		for ( int Row = 0; Row < Height; ++Row )
		{
			std::vector<char> NewRow;
			for ( int Col = 0; Col < Width; ++Col )
			{
				NewRow.push_back('.');
			}
			Grid.push_back( NewRow );
		}
	}

	void InitSensors( const std::vector<Sensor>& InSensors )
	{
		for ( const Sensor& Curr : InSensors )
		{
			if ( IsValidGridElement( Curr.Pos ) )
			{
				GetGridElement( Curr.Pos ) = 'S';
			}

			if ( IsValidGridElement( Curr.ClosestBeaconPos ) )
			{
				GetGridElement( Curr.ClosestBeaconPos ) = 'B';
			}
		}
	}

	void RecordSensorArea( const Sensor& InSensor )
	{
		for ( int Row = RowOffset; Row < (int)Grid.size() + RowOffset; ++Row )
		{
			for ( int Col = ColOffset; Col < ( int )Grid[0].size() + ColOffset; ++Col )
			{
				IntVector2D Pos( Col, Row );
				if ( IsWithinRange(Pos, InSensor.Pos, InSensor.DistToBeacon) )
				{
					char& GridElem = GetGridElement( Pos );
					if ( GridElem == '.' )
					{
						GridElem = '#';
					}
				}
			}
		}
	}

	int GetEmptyPosCountInRow( int Row ) const
	{
		const std::vector<char>& SelectedRow = Grid[Row + RowOffset];

		int EmptySpaceCt = 0;
		for ( char Entry : SelectedRow )
		{
			if ( Entry == '#' )
			{
				++EmptySpaceCt;
			}
		}

		return EmptySpaceCt;
	}

	void Print( const std::vector<IntVector2D>& InPoints ) const
	{
		std::vector<std::vector<char>> PathData;
		const size_t RowCt = Grid.size();
		const size_t ColCt = Grid[0].size();
		for ( size_t Row = 0; Row < RowCt; ++Row )
		{
			std::vector<char> NewRow;
			for ( size_t Col = 0; Col < ColCt; ++Col )
			{
				NewRow.push_back( Grid[Row][Col] );
			}
			PathData.push_back( NewRow );
		}

		for ( const IntVector2D& Entry : InPoints )
		{
			int X = Entry.X - ColOffset;
			int Y = Entry.Y - RowOffset;
			PathData[X][Y] = 'A';
		}

		for ( const std::vector<char>& Row : PathData )
		{
			for ( char Entry : Row )
			{
				std::cout << Entry;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Print() const
	{
		int Ct = RowOffset;
		for ( const std::vector<char>& Row : Grid )
		{
			std::cout << Ct << " ";
			if ( Ct < 10 && Ct >= 0)
			{
				std::cout << " ";
			}

			for ( char Entry : Row )
			{

				std::cout << Entry;
			}
			std::cout << std::endl;
			++Ct;
		}
		std::cout << std::endl;
	}

	char& GetGridElement( const IntVector2D& InPos )
	{
		return GetGridElement( InPos.X, InPos.Y );
	}

	char& GetGridElement( int RawX, int RawY )
	{
		int Col = RawX - ColOffset;
		int Row = RawY - RowOffset;
		return Grid[Row][Col];
	}

	bool IsValidGridElement( const IntVector2D& InPos ) const
	{
		return IsValidGridElement( InPos.X, InPos.Y );
	}

	bool IsValidGridElement( int RawX, int RawY ) const
	{
		int Col = RawX - ColOffset;
		int Row = RawY - RowOffset;
		return Row >= 0 && Row < ( int )Grid.size() && Col >= 0 && Col < ( int )Grid[0].size();
	}

	std::vector<std::vector<char>> Grid;
	int ColOffset;
	int RowOffset;

};

void GetDay15Range( const std::vector<Sensor>& InSensors, int& MinX, int& MaxX, int& MinY, int& MaxY )
{
	MinX = INT_MAX;
	MaxX = INT_MIN;
	MinY = INT_MAX;
	MaxY = INT_MIN;

	for ( const Sensor& Curr : InSensors )
	{
		MinX = std::min( MinX, std::min( Curr.Pos.X, Curr.ClosestBeaconPos.X ) );
		MaxX = std::max( MaxX, std::max( Curr.Pos.X, Curr.ClosestBeaconPos.X ) );
		MinY = std::min( MinY, std::min( Curr.Pos.Y, Curr.ClosestBeaconPos.Y ) );
		MaxY = std::max( MaxY, std::max( Curr.Pos.Y, Curr.ClosestBeaconPos.Y ) );
	}
}

void GetDay15RangeWithDistance( const std::vector<Sensor>& InSensors, int& MinX, int& MaxX, int& MinY, int& MaxY )
{
	MinX = INT_MAX;
	MaxX = INT_MIN;
	MinY = INT_MAX;
	MaxY = INT_MIN;

	for ( const Sensor& Curr : InSensors )
	{
		MinX = std::min( MinX, Curr.Pos.X - Curr.DistToBeacon);
		MaxX = std::max( MaxX, Curr.Pos.X + Curr.DistToBeacon);
		MinY = std::min( MinY, Curr.Pos.Y - Curr.DistToBeacon );
		MaxY = std::max( MaxY, Curr.Pos.Y + Curr.DistToBeacon );
	}
}

int Day15Part1( const std::string& Filename, int AnswerRow, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<Sensor> Sensors;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Sensor NewSensor;
		NewSensor.Init( Line );
		Sensors.push_back( NewSensor );
	}

	myfile.close();

	int MinX, MaxX, MinY, MaxY;
	GetDay15RangeWithDistance( Sensors, MinX, MaxX, MinY, MaxY );

	std::vector<Sensor> RelevantSensors;
	for ( const Sensor& Curr : Sensors )
	{
		if ( std::abs( AnswerRow - Curr.Pos.Y ) <= Curr.DistToBeacon )
		{
			RelevantSensors.push_back( Curr );
		}
	}

	int EmptyPosCount = 0;
	for ( int Col = MinX; Col < MaxX; ++Col )
	{
		bool bObjectPresent = false;
		bool bWithinRange = false;
		IntVector2D CurrPos = IntVector2D( Col, AnswerRow );
		for ( const Sensor& CurrSensor : Sensors )
		{
			if ( IsWithinRange( CurrSensor.Pos, CurrPos, CurrSensor.DistToBeacon ) )
			{
				bWithinRange = true;
			}

			if ( CurrSensor.ClosestBeaconPos == CurrPos)
			{
				bObjectPresent = true;
				break;
			}
		}

		if ( bWithinRange && !bObjectPresent )
		{
			++EmptyPosCount;
		}
	}

	if ( bShouldPrint )
	{
		GetDay15Range( Sensors, MinX, MaxX, MinY, MaxY );
		CaveSystem Caves( MinX, MaxX + 1, MinY, MaxY + 1 );
		Caves.InitSensors( Sensors );
		if ( bShouldPrint )
		{
			Caves.Print();
		}

		for ( const Sensor& Curr : RelevantSensors )
		{
			Caves.RecordSensorArea( Curr );
		}

		//Caves.RecordSensorArea( RelevantSensors.front() );
		if ( bShouldPrint )
		{
			Caves.Print();
		}

		//return Caves.GetEmptyPosCountInRow( AnswerRow );
	}

	return EmptyPosCount;
}

// Does not clear OutPoints before appending
void GetRadiusFromSensor( const Sensor& InSensor, std::vector<IntVector2D>& OutPoints )
{
	int Radius = InSensor.DistToBeacon + 1;
	IntVector2D SenserPos = InSensor.Pos;
	
	for ( int Idx = 0; Idx < Radius; ++Idx )
	{
		int NewX = Radius - Idx;
		int NewY = Idx;
		IntVector2D Up( NewX, -NewY );
		IntVector2D Right( NewX, NewY );
		IntVector2D Down( -NewX, NewY );
		IntVector2D Left( -NewX, -NewY );
		OutPoints.push_back( Up + SenserPos );
		OutPoints.push_back( Right + SenserPos );
		OutPoints.push_back( Down + SenserPos );
		OutPoints.push_back( Left + SenserPos );
	}
}

unsigned long long Day15Part2( const std::string& Filename, int Range, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<Sensor> Sensors;
	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );

		Sensor NewSensor;
		NewSensor.Init( Line );
		Sensors.push_back( NewSensor );
	}

	myfile.close();

	int MinX, MaxX, MinY, MaxY;
	GetDay15RangeWithDistance( Sensors, MinX, MaxX, MinY, MaxY );

	std::vector<Sensor> RelevantSensors;
	std::vector<IntVector2D> Points;
	for ( const Sensor& Curr : Sensors )
	{
		GetRadiusFromSensor( Curr, Points );
		

		//if ( std::abs( AnswerRow - Curr.Pos.Y ) <= Curr.DistToBeacon )
		{
		//	RelevantSensors.push_back( Curr );
		}
	}

	unsigned long long Output = 0;
	for ( const IntVector2D& Point : Points )
	{
		if ( Point.X < 0 || Point.Y < 0 || Point.X > Range || Point.Y > Range )
		{
			continue;
		}

		bool bFoundOverlap = false;
		for ( const Sensor& Curr : Sensors )
		{
			if ( IsWithinRange( Curr.Pos, Point, Curr.DistToBeacon ) )
			{
				bFoundOverlap = true;
				break;
			}
		}

		if ( !bFoundOverlap )
		{
			// By the skin of my teeth. This answer is TOO BIG for unsigned long long. Have to calculate separately.
			Output = Point.X * 4000000 + Point.Y;
			std::cout << Point.X << "," << Point.Y << ": " << Output << std::endl;
			break;
		}
	}


	/*
	for ( int Col = MinX; Col < MaxX; ++Col )
	{
		bool bObjectPresent = false;
		bool bWithinRange = false;
		IntVector2D CurrPos = IntVector2D( Col, AnswerRow );
		for ( const Sensor& CurrSensor : Sensors )
		{
			if ( IsWithinRange( CurrSensor.Pos, CurrPos, CurrSensor.DistToBeacon ) )
			{
				bWithinRange = true;
			}

			if ( CurrSensor.ClosestBeaconPos == CurrPos )
			{
				bObjectPresent = true;
				break;
			}
		}

		if ( bWithinRange && !bObjectPresent )
		{
			++EmptyPosCount;
		}
	}
	//*/

	//*
	if ( bShouldPrint )
	{
		GetDay15Range( Sensors, MinX, MaxX, MinY, MaxY );
		CaveSystem Caves( MinX, MaxX + 1, MinY, MaxY + 1 );
		Caves.InitSensors( Sensors );
		if ( bShouldPrint )
		{
			Caves.Print();
		}
		for ( const Sensor& Curr : Sensors )
		{
			Caves.RecordSensorArea( Curr );
			if ( bShouldPrint )
			{
				Caves.Print();
			}
		}

		Caves.RecordSensorArea( Sensors.front() );
		if ( bShouldPrint )
		{
			Caves.Print();
		}

		//return Caves.GetEmptyPosCountInRow( AnswerRow );
	}

	//*/
	return Output;
}

struct Valve
{
	std::string Name;
	std::vector<std::string> Connections;
	int FlowRate = -1;
};

struct VolcanoNetwork
{
	std::vector<Valve> Valves;

	void AddValve( const std::string& InLine )
	{
		Valve NewValve;

		NewValve.Name = InLine.substr( 6, 2 );

		size_t Start = 23U;
		size_t End = Start;
		NewValve.FlowRate = stoi( InLine.substr( Start, InLine.find( ';', Start ) ) );

		// Get kinda close, then hone in on the end;
		Start += 24;
		Start = InLine.find(' ', Start);
		++Start;

		do
		{
			End = InLine.find( ',', Start );
			NewValve.Connections.push_back( InLine.substr( Start, End - Start ) );
			Start = End + 2;

		} while ( End != std::string::npos );

		Valves.push_back( NewValve );
	}

	const Valve* GetValve( const std::string& ValveName ) const
	{
		for ( size_t Idx = 0; Idx < Valves.size(); ++Idx )
		{
			const Valve& CurrValve = Valves[Idx];
			if ( CurrValve.Name == ValveName )
			{
				return &Valves[Idx];
			}
		}
	}

	int SolveNetwork() const
	{
		struct Node
		{
			Node() {}

			const Valve* pValve = nullptr;
			const Node* pPrev = nullptr;
			int TotalPressure = 0;
			int TimeElapsed = 0;
		};

		std::queue<Node*> WaitingNodes;

		Node* FirstNode = new Node();
		FirstNode->TotalPressure = Valves[0].FlowRate;
		FirstNode->pValve = &Valves[0];
		WaitingNodes.push( FirstNode );

		while ( WaitingNodes.size() > 0 )
		{
			Node* CurrNode = WaitingNodes.front();
			WaitingNodes.pop();

			for ( const std::string& NextNode : CurrNode->pValve->Connections )
			{
				Node* NewNode = new Node();
				NewNode->pValve = GetValve(NextNode);
				NewNode->TotalPressure = Valves[0].FlowRate;
				NewNode->TimeElapsed = CurrNode->TimeElapsed + 1;
				WaitingNodes.push( FirstNode );
			}
		}

		return 0;
	}
	
	std::vector<Valve> OpenValves;
	int PressureReleased = 0;
	int RemainingTime = 30;
};

unsigned long long Day16Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	VolcanoNetwork Network;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
		Network.AddValve( Line );
	}

	myfile.close();

	long long Output = 0;
	return Output;
}


unsigned long long Day16Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	VolcanoNetwork Network;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
		Network.AddValve( Line );
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

template <typename T>
struct RingBuffer
{
	const T& GetNext() const
	{
		if (Data.size() == 0)
		{
			return T();
		}

		const T& Output = Data[CurrIdx++];
		if (CurrIdx >= Data.size())
		{
			CurrIdx = 0;
		}
		return Output;
	}

	void push_back(const T& InItem)
	{
		Data.push_back(InItem);
	}

private:
	std::vector<T> Data;
	mutable size_t CurrIdx = 0;
};

struct VolcanoRock
{
	std::vector<IntVector2D> RockLocs;
	IntVector2D Position;
	int Height = 0;
};

struct CaveSlice
{
	const int CaveWidth = 7;

	// Row 0 is the floor row. Highest rows are at the highest indices
	std::vector<std::vector<char>> CaveLines;

	void AddEmptyRow(char LineChar = '.')
	{
		std::vector<char> NewLine;
		NewLine.push_back('#');
		for (int Ct = 0; Ct < CaveWidth; ++Ct)
		{
			NewLine.push_back(LineChar);
		}
		NewLine.push_back('#');
		CaveLines.push_back(NewLine);
	}

	void AddRock(const VolcanoRock& InRock, RingBuffer<char>& InGasQueue)
	{
		for (int Ct = 0; Ct < InRock.Height; ++Ct)
		{
			AddEmptyRow();
		}

		VolcanoRock CurrRock = InRock;
		CurrRock.Position = IntVector2D(2, 0);

		for (const IntVector2D& RockPos : CurrRock.RockLocs)
		{
			UpdatePosition(RockPos + CurrRock.Position, '#');

			// If rock is touching a rock ('#'), stop the fall
			if (false)
			{
				break;
			}

			// Apply Gas
			char GasDir = InGasQueue.GetNext();
			if (GasDir == '>')
			{
				++CurrRock.Position.Y;
			}

			++CurrRock.Position.X;
		}
	}

	void UpdatePosition(const IntVector2D& Pos, char InChar)
	{
		IntVector2D ActualPos = IntVector2D(Pos.X, static_cast<int>(CaveLines.size()) - 1 - Pos.Y);

		CaveLines[ActualPos.Y][ActualPos.X] = InChar;
	}

	void Print() const
	{
		for (int Row = static_cast<int>(CaveLines.size()) - 1; Row >= 0; --Row)
		{
			for (char Val : CaveLines[Row])
			{
				std::cout << Val;
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};

unsigned long long Day17Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	// Rock root is always the bottom left corner
	/* #### */
	VolcanoRock Rock0;
	Rock0.RockLocs.push_back(IntVector2D(0, 0));
	Rock0.RockLocs.push_back(IntVector2D(1, 0));
	Rock0.RockLocs.push_back(IntVector2D(2, 0));
	Rock0.RockLocs.push_back(IntVector2D(3, 0));
	Rock0.Height = 1;

	/*
	.#.
	###
	.#.
	*/
	VolcanoRock Rock1;
	Rock1.RockLocs.push_back(IntVector2D(1, 1));
	Rock1.RockLocs.push_back(IntVector2D(0, 0));
	Rock1.RockLocs.push_back(IntVector2D(1, 0));
	Rock1.RockLocs.push_back(IntVector2D(2, 0));
	Rock1.RockLocs.push_back(IntVector2D(1, -1));
	Rock1.Height = 3;

	/*
	..#
	..#
	###
	*/
	VolcanoRock Rock2;
	Rock2.RockLocs.push_back(IntVector2D(0, 0));
	Rock2.RockLocs.push_back(IntVector2D(1, 0));
	Rock2.RockLocs.push_back(IntVector2D(2, 0));
	Rock2.RockLocs.push_back(IntVector2D(2, 1));
	Rock2.RockLocs.push_back(IntVector2D(2, 2));
	Rock2.Height = 3;

	/*
	#
	#
	#
	#
	*/
	VolcanoRock Rock3;
	Rock3.RockLocs.push_back(IntVector2D(0, 0));
	Rock3.RockLocs.push_back(IntVector2D(0, 1));
	Rock3.RockLocs.push_back(IntVector2D(0, 2));
	Rock3.RockLocs.push_back(IntVector2D(0, 3));
	Rock3.Height = 4;

	/*
	##
	##
	*/
	VolcanoRock Rock4;
	Rock4.RockLocs.push_back(IntVector2D(0, 0));
	Rock4.RockLocs.push_back(IntVector2D(0, 1));
	Rock4.RockLocs.push_back(IntVector2D(1, 0));
	Rock4.RockLocs.push_back(IntVector2D(1, 1));
	Rock4.Height = 2;

	//std::vector<VolcanoRock> RockQueue({ Rock0, Rock1, Rock2, Rock3, Rock4 });
	//std::vector<char> GasQueue;

	RingBuffer<VolcanoRock> RockQueue;
	RockQueue.push_back(Rock0);
	RockQueue.push_back(Rock1);
	RockQueue.push_back(Rock2);
	RockQueue.push_back(Rock3);
	RockQueue.push_back(Rock4);

	RingBuffer<char> GasQueue;

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);

		for (const char& Dir : Line)
		{
			GasQueue.push_back(Dir);
		}
	}

	myfile.close();

	CaveSlice FallingRockSim;
	FallingRockSim.AddEmptyRow('+');
	FallingRockSim.AddEmptyRow();
	FallingRockSim.AddEmptyRow();

	FallingRockSim.Print();

	int RockCt = 0;
	const int RockGoal = 1;
	while (RockCt < RockGoal)
	{
		FallingRockSim.AddRock(RockQueue.GetNext(), GasQueue);
		FallingRockSim.Print();
	}

	long long Output = 0;
	return Output;
}

unsigned long long Day17Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day18Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day18Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day19Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day19Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day20Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day20Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day21Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day21Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day22Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day22Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day23Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day23Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day24Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day24Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day25Part1(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

unsigned long long Day25Part2(const std::string& Filename, bool bShouldPrint = false)
{
	std::ifstream myfile;
	myfile.open(Filename);

	while (myfile.good())
	{
		char line[4096];
		myfile.getline(line, 4096);
		std::string Line(line);
	}

	myfile.close();

	long long Output = 0;
	return Output;
}

int main()
{
	/*
	std::string Day1Sample( "..\\..\\Day1Sample.txt" );
	std::string Day1Input( "..\\..\\Day1Input.txt" );
	std::cout << "Day1Part1Sample: " << Year22Day1Part1( Day1Sample ) << std::endl;
	std::cout << "Day1Part1: " << Year22Day1Part1( Day1Input ) << std::endl
	std::cout << "Day1Part2Sample: " << Year22Day1Part2( Day1Sample ) << std::endl;
	std::cout << "Day1Part2: " << Year22Day1Part2( Day1Input ) << std::endl;



	std::string Day2Sample( "..\\..\\Day2Sample.txt" );
	std::string Day2Input( "..\\..\\Day2Input.txt" );
	std::cout << "Day2Part1Sample: " << Day2Part1( Day2Sample ) << std::endl;
	std::cout << "Day2Part1: " << Day2Part1( Day2Input ) << std::endl;
	std::cout << "Day2Part2Sample: " << Day2Part2( Day2Sample ) << std::endl;
	std::cout << "Day2Part2: " << Day2Part2( Day2Input ) << std::endl;



	std::string Day3Sample( "..\\..\\Day3Sample.txt" );
	std::string Day3Input( "..\\..\\Day3Input.txt" );
	std::cout << "Day3Part1Sample: " << Day3Part1( Day3Sample ) << std::endl;
	std::cout << "Day3Part1: " << Day3Part1( Day3Input ) << std::endl;
	std::cout << "Day3Part2Sample: " << Day3Part2( Day3Sample ) << std::endl;
	std::cout << "Day3Part2: " << Day3Part2( Day3Input ) << std::endl;



	std::string Day4Sample( "..\\..\\Day4Sample.txt" );
	std::string Day4Input( "..\\..\\Day4Input.txt" );
	std::cout << "Day4Part1Sample: " << Day4Part1( Day4Sample ) << std::endl;
	std::cout << "Day4Part1: " << Day4Part1( Day4Input ) << std::endl;
	std::cout << "Day4Part2Sample: " << Day4Part2( Day4Sample ) << std::endl;
	std::cout << "Day4Part2: " << Day4Part2( Day4Input ) << std::endl;


	LoadingDock SampleStacks;
	{
		std::stack<char> Stack0;
		Stack0.push( 'z' );
		Stack0.push( 'n' );
		std::stack<char> Stack1;
		Stack1.push( 'm' );
		Stack1.push( 'c' );
		Stack1.push( 'd' );
		std::stack<char> Stack2;
		Stack2.push( 'p' );
		SampleStacks.Stacks.push_back( Stack0 );
		SampleStacks.Stacks.push_back( Stack1 );
		SampleStacks.Stacks.push_back( Stack2 );
	}

	LoadingDock InputStacks;
	{
		std::stack<char> Stack0;
		Stack0.push( 's' );
		Stack0.push( 'c' );
		Stack0.push( 'v' );
		Stack0.push( 'n' );
		std::stack<char> Stack1;
		Stack1.push( 'z' );
		Stack1.push( 'm' );
		Stack1.push( 'j' );
		Stack1.push( 'h' );
		Stack1.push( 'n' );
		Stack1.push( 's' );
		std::stack<char> Stack2;
		Stack2.push( 'm' );
		Stack2.push( 'c' );
		Stack2.push( 't' );
		Stack2.push( 'g' );
		Stack2.push( 'j' );
		Stack2.push( 'n' );
		Stack2.push( 'd' );
		std::stack<char> Stack3;
		Stack3.push( 't' );
		Stack3.push( 'd' );
		Stack3.push( 'f' );
		Stack3.push( 'j' );
		Stack3.push( 'w' );
		Stack3.push( 'r' );
		Stack3.push( 'm' );
		std::stack<char> Stack4;
		Stack4.push( 'p' );
		Stack4.push( 'f' );
		Stack4.push( 'h' );
		std::stack<char> Stack5;
		Stack5.push( 'c' );
		Stack5.push( 't' );
		Stack5.push( 'z' );
		Stack5.push( 'h' );
		Stack5.push( 'j' );
		std::stack<char> Stack6;
		Stack6.push( 'd' );
		Stack6.push( 'p' );
		Stack6.push( 'r' );
		Stack6.push( 'q' );
		Stack6.push( 'f' );
		Stack6.push( 's' );
		Stack6.push( 'l' );
		Stack6.push( 'z' );
		std::stack<char> Stack7;
		Stack7.push( 'c' );
		Stack7.push( 's' );
		Stack7.push( 'l' );
		Stack7.push( 'h' );
		Stack7.push( 'd' );
		Stack7.push( 'f' );
		Stack7.push( 'p' );
		Stack7.push( 'w' );
		std::stack<char> Stack8;
		Stack8.push( 'd' );
		Stack8.push( 's' );
		Stack8.push( 'm' );
		Stack8.push( 'p' );
		Stack8.push( 'f' );
		Stack8.push( 'n' );
		Stack8.push( 'g' );
		Stack8.push( 'z' );
		InputStacks.Stacks.push_back( Stack0 );
		InputStacks.Stacks.push_back( Stack1 );
		InputStacks.Stacks.push_back( Stack2 );
		InputStacks.Stacks.push_back( Stack3 );
		InputStacks.Stacks.push_back( Stack4 );
		InputStacks.Stacks.push_back( Stack5 );
		InputStacks.Stacks.push_back( Stack6 );
		InputStacks.Stacks.push_back( Stack7 );
		InputStacks.Stacks.push_back( Stack8 );
	}

	std::string Day5Sample( "..\\..\\Day5Sample.txt" );
	std::string Day5Input( "..\\..\\Day5Input.txt" );
	std::cout << "Day5Part1Sample: " << Day5Part1( Day5Sample, 5, SampleStacks ) << std::endl;
	std::cout << "Day5Part1: " << Day5Part1( Day5Input, 10, InputStacks ) << std::endl;
	std::cout << "Day5Part2Sample: " << Day5Part2( Day5Sample, 5, SampleStacks ) << std::endl;
	std::cout << "Day5Part2: " << Day5Part2( Day5Input, 10, InputStacks ) << std::endl;



	std::string Day6Sample( "..\\..\\Day6Sample.txt" );
	std::string Day6Input( "..\\..\\Day6Input.txt" );
	std::cout << "Day6Part1Sample: " << Day6Part1( Day6Sample ) << std::endl;
	std::cout << "Day6Part1: " << Day6Part1( Day6Input ) << std::endl;
	std::cout << "Day6Part2Sample: " << Day6Part2( Day6Sample ) << std::endl;
	std::cout << "Day6Part2: " << Day6Part2( Day6Input ) << std::endl;


	std::string Day7Sample( "..\\..\\Day7Sample.txt" );
	std::string Day7Input( "..\\..\\Day7Input.txt" );
	std::cout << "Day7Part1Sample: " << Day7Part1( Day7Sample ) << std::endl;
	std::cout << "Day7Part1: " << Day7Part1( Day7Input ) << std::endl;
	std::cout << "Day7Part2Sample: " << Day7Part2( Day7Sample ) << std::endl;
	std::cout << "Day7Part2: " << Day7Part2( Day7Input ) << std::endl;

	std::string Day8Sample( "..\\..\\Day8Sample.txt" );
	std::string Day8Input( "..\\..\\Day8Input.txt" );
	std::cout << "Day8Part1Sample: " << Day8Part1( Day8Sample ) << std::endl;
	std::cout << "Day8Part1: " << Day8Part1( Day8Input ) << std::endl;
	std::cout << "Day8Part2Sample: " << Day8Part2( Day8Sample ) << std::endl;
	std::cout << "Day8Part2: " << Day8Part2( Day8Input ) << std::endl;

	std::string Day9Sample( "..\\..\\Day9Sample.txt" );
	std::string Day9Input( "..\\..\\Day9Input.txt" );
	std::cout << "Day9Part1Sample: " << Day9Part1( Day9Sample, true ) << std::endl;
	std::cout << "Day9Part1: " << Day9Part1( Day9Input ) << std::endl;
	std::cout << "Day9Part2Sample: " << Day9Part2( Day9Sample, true ) << std::endl;
	std::cout << "Day9Part2: " << Day9Part2( Day9Input ) << std::endl;

	std::string Day10Sample( "..\\..\\Day10Sample.txt" );
	std::string Day10Input( "..\\..\\Day10Input.txt" );
	std::cout << "Day10Part1Sample: " << Day10Part1( Day10Sample ) << std::endl;
	std::cout << "Day10Part1: " << Day10Part1( Day10Input ) << std::endl;
	std::cout << "Day10Part2Sample: " << Day10Part2( Day10Sample ) << std::endl;
	std::cout << "Day10Part2: " << Day10Part2( Day10Input ) << std::endl;

	Monkey SampleMonkey0;
	SampleMonkey0.HeldItems = { 79, 98 };
	SampleMonkey0.Operation = []( unsigned long long Old ) { return Old * 19; };
	SampleMonkey0.Divisor = 23;
	SampleMonkey0.TrueDest = 2;
	SampleMonkey0.FalseDest = 3;

	Monkey SampleMonkey1;
	SampleMonkey1.HeldItems = { 54, 65, 75, 74 };
	SampleMonkey1.Operation = []( unsigned long long Old ) { return Old + 6; };
	SampleMonkey1.Divisor = 19;
	SampleMonkey1.TrueDest = 2;
	SampleMonkey1.FalseDest = 0;

	Monkey SampleMonkey2;
	SampleMonkey2.HeldItems = { 79, 60, 97 };
	SampleMonkey2.Operation = []( unsigned long long Old ) { return Old * Old; };
	SampleMonkey2.Divisor = 13;
	SampleMonkey2.TrueDest = 1;
	SampleMonkey2.FalseDest = 3;

	Monkey SampleMonkey3;
	SampleMonkey3.HeldItems = { 74 };
	SampleMonkey3.Operation = []( unsigned long long Old ) { return Old + 3; };
	SampleMonkey3.Divisor = 17;
	SampleMonkey3.TrueDest = 0;
	SampleMonkey3.FalseDest = 1;

	std::vector<Monkey> SampleMonkeys( { SampleMonkey0, SampleMonkey1, SampleMonkey2, SampleMonkey3 } );
	std::vector<Monkey> SampleMonkeysPt2( { SampleMonkey0, SampleMonkey1, SampleMonkey2, SampleMonkey3 } );

	Monkey Monkey0;
	Monkey0.HeldItems = { 75, 63 };
	Monkey0.Operation = []( unsigned long long Old ) { return Old * 3; };
	Monkey0.Divisor = 11;
	Monkey0.TrueDest = 7;
	Monkey0.FalseDest = 2;

	Monkey Monkey1;
	Monkey1.HeldItems = { 65, 79, 98, 77, 56, 54, 83, 94 };
	Monkey1.Operation = []( unsigned long long Old ) { return Old + 3; };
	Monkey1.Divisor = 2;
	Monkey1.TrueDest = 2;
	Monkey1.FalseDest = 0;

	Monkey Monkey2;
	Monkey2.HeldItems = { 66 };
	Monkey2.Operation = []( unsigned long long Old ) { return Old + 5; };
	Monkey2.Divisor = 5;
	Monkey2.TrueDest = 7;
	Monkey2.FalseDest = 5;

	Monkey Monkey3;
	Monkey3.HeldItems = { 51, 89, 90 };
	Monkey3.Operation = []( unsigned long long Old ) { return Old * 19; };
	Monkey3.Divisor = 7;
	Monkey3.TrueDest = 6;
	Monkey3.FalseDest = 4;

	Monkey Monkey4;
	Monkey4.HeldItems = { 75, 94, 66, 90, 77, 82, 61 };
	Monkey4.Operation = []( unsigned long long Old ) { return Old + 1; };
	Monkey4.Divisor = 17;
	Monkey4.TrueDest = 6;
	Monkey4.FalseDest = 1;

	Monkey Monkey5;
	Monkey5.HeldItems = { 53, 76, 59, 92, 95 };
	Monkey5.Operation = []( unsigned long long Old ) { return Old + 2; };
	Monkey5.Divisor = 19;
	Monkey5.TrueDest = 4;
	Monkey5.FalseDest = 3;

	Monkey Monkey6;
	Monkey6.HeldItems = { 81, 61, 75, 89, 70, 92 };
	Monkey6.Operation = []( unsigned long long Old ) { return Old * Old; };
	Monkey6.Divisor = 3;
	Monkey6.TrueDest = 0;
	Monkey6.FalseDest = 1;

	Monkey Monkey7;
	Monkey7.HeldItems = { 81, 86, 62, 87 };
	Monkey7.Operation = []( unsigned long long Old ) { return Old + 8; };
	Monkey7.Divisor = 13;
	Monkey7.TrueDest = 3;
	Monkey7.FalseDest = 5;

	std::vector<Monkey> Monkeys( { Monkey0, Monkey1, Monkey2, Monkey3, Monkey4, Monkey5, Monkey6, Monkey7 } );
	std::vector<Monkey> MonkeysPt2( { Monkey0, Monkey1, Monkey2, Monkey3, Monkey4, Monkey5, Monkey6, Monkey7 } );

	std::cout << "Day11Part1Sample: " << Day11Part1( SampleMonkeys ) << std::endl;
	std::cout << "Day11Part1: " << Day11Part1( Monkeys ) << std::endl;
	std::cout << "Day11Part2Sample: " << Day11Part2( SampleMonkeysPt2 ) << std::endl;
	std::cout << "Day11Part2: " << Day11Part2( MonkeysPt2 ) << std::endl;

	std::string Day12Sample( "..\\..\\Day12Sample.txt" );
	std::string Day12Input( "..\\..\\Day12Input.txt" );
	std::cout << "Day12Part1Sample: " << Day12Part1( Day12Sample, true ) << std::endl;
	std::cout << "Day12Part1: " << Day12Part1( Day12Input, true ) << std::endl;
	std::cout << "Day12Part2Sample: " << Day12Part2( Day12Sample ) << std::endl;
	std::cout << "Day12Part2: " << Day12Part2( Day12Input ) << std::endl;

	std::string Day13Sample( "..\\..\\Day13Sample.txt" );
	std::string Day13Input( "..\\..\\Day13Input.txt" );
	std::cout << "Day13Part1Sample: " << Day13Part1( Day13Sample ) << std::endl;
	std::cout << "Day13Part1: " << Day13Part1( Day13Input) << std::endl;
	std::cout << "Day13Part2Sample: " << Day13Part2( Day13Sample, true ) << std::endl;
	std::cout << "Day13Part2: " << Day13Part2( Day13Input ) << std::endl;

	std::string Day14Sample( "..\\..\\Day14Sample.txt" );
	std::string Day14Input( "..\\..\\Day14Input.txt" );
	std::cout << "Day14Part1Sample: " << Day14Part1( Day14Sample ) << std::endl;
	std::cout << "Day14Part1: " << Day14Part1( Day14Input ) << std::endl;
	std::cout << "Day14Part2Sample: " << Day14Part2( Day14Sample, true ) << std::endl;
	std::cout << "Day14Part2: " << Day14Part2( Day14Input ) << std::endl;

	std::string Day15Sample( "..\\..\\Day15Sample.txt" );
	std::string Day15Input( "..\\..\\Day15Input.txt" );
	std::cout << "Day15Part1Sample: " << Day15Part1( Day15Sample, 10, true ) << std::endl;
	std::cout << "Day15Part1: " << Day15Part1( Day15Input, 2000000 ) << std::endl;
	std::cout << "Day15Part2Sample: " << Day15Part2( Day15Sample, 20, true ) << std::endl;
	std::cout << "Day15Part2: " << Day15Part2( Day15Input, 4000000 ) << std::endl;
	//*/

	/*
	std::string Day16Sample( "..\\..\\Day16Sample.txt" );
	std::string Day16Input( "..\\..\\Day16Input.txt" );
	std::cout << "Day16Part1Sample: " << Day16Part1( Day16Sample ) << std::endl;
	std::cout << "Day16Part1: " << Day16Part1( Day16Input ) << std::endl;
	std::cout << "Day16Part2Sample: " << Day16Part2( Day16Sample, true ) << std::endl;
	std::cout << "Day16Part2: " << Day16Part2( Day16Input ) << std::endl;
	//*/

	//*
	std::string Day17Sample("..\\..\\Day17Sample.txt");
	std::string Day17Input("..\\..\\Day17Input.txt");
	std::cout << "Day17Part1Sample: " << Day17Part1(Day17Sample) << std::endl;
	std::cout << "Day17Part1: " << Day17Part1(Day17Input) << std::endl;
	//std::cout << "Day17Part2Sample: " << Day17Part2(Day17Sample, true) << std::endl;
	//std::cout << "Day17Part2: " << Day17Part2(Day17Input) << std::endl;
	//*/

	/*
	std::string Day18Sample("..\\..\\Day18Sample.txt");
	std::string Day18Input("..\\..\\Day18Input.txt");
	std::cout << "Day18Part1Sample: " << Day18Part1(Day18Sample) << std::endl;
	std::cout << "Day18Part1: " << Day18Part1(Day18Input) << std::endl;
	std::cout << "Day18Part2Sample: " << Day18Part2(Day18Sample, true) << std::endl;
	std::cout << "Day18Part2: " << Day18Part2(Day18Input) << std::endl;
	//*/

	/*
	std::string Day19Sample("..\\..\\Day19Sample.txt");
	std::string Day19Input("..\\..\\Day19Input.txt");
	std::cout << "Day19Part1Sample: " << Day19Part1(Day19Sample) << std::endl;
	std::cout << "Day19Part1: " << Day19Part1(Day19Input) << std::endl;
	std::cout << "Day19Part2Sample: " << Day19Part2(Day19Sample, true) << std::endl;
	std::cout << "Day19Part2: " << Day19Part2(Day19Input) << std::endl;
	//*/

	/*
	std::string Day20Sample("..\\..\\Day20Sample.txt");
	std::string Day20Input("..\\..\\Day20Input.txt");
	std::cout << "Day20Part1Sample: " << Day20Part1(Day20Sample) << std::endl;
	std::cout << "Day20Part1: " << Day20Part1(Day20Input) << std::endl;
	std::cout << "Day20Part2Sample: " << Day20Part2(Day20Sample, true) << std::endl;
	std::cout << "Day20Part2: " << Day20Part2(Day20Input) << std::endl;
	//*/

	/*
	std::string Day21Sample("..\\..\\Day21Sample.txt");
	std::string Day21Input("..\\..\\Day21Input.txt");
	std::cout << "Day21Part1Sample: " << Day21Part1(Day21Sample) << std::endl;
	std::cout << "Day21Part1: " << Day21Part1(Day21Input) << std::endl;
	std::cout << "Day21Part2Sample: " << Day21Part2(Day21Sample, true) << std::endl;
	std::cout << "Day21Part2: " << Day21Part2(Day21Input) << std::endl;
	//*/

	/*
	std::string Day22Sample("..\\..\\Day22Sample.txt");
	std::string Day22Input("..\\..\\Day22Input.txt");
	std::cout << "Day22Part1Sample: " << Day22Part1(Day22Sample) << std::endl;
	std::cout << "Day22Part1: " << Day22Part1(Day22Input) << std::endl;
	std::cout << "Day22Part2Sample: " << Day22Part2(Day22Sample, true) << std::endl;
	std::cout << "Day22Part2: " << Day22Part2(Day22Input) << std::endl;
	//*/

	/*
	std::string Day23Sample("..\\..\\Day23Sample.txt");
	std::string Day23Input("..\\..\\Day23Input.txt");
	std::cout << "Day23Part1Sample: " << Day23Part1(Day23Sample) << std::endl;
	std::cout << "Day23Part1: " << Day23Part1(Day23Input) << std::endl;
	std::cout << "Day23Part2Sample: " << Day23Part2(Day23Sample, true) << std::endl;
	std::cout << "Day23Part2: " << Day23Part2(Day23Input) << std::endl;
	//*/

	/*
	std::string Day24Sample("..\\..\\Day24Sample.txt");
	std::string Day24Input("..\\..\\Day24Input.txt");
	std::cout << "Day24Part1Sample: " << Day24Part1(Day24Sample) << std::endl;
	std::cout << "Day24Part1: " << Day24Part1(Day24Input) << std::endl;
	std::cout << "Day24Part2Sample: " << Day24Part2(Day24Sample, true) << std::endl;
	std::cout << "Day24Part2: " << Day24Part2(Day24Input) << std::endl;
	//*/

	/*
	std::string Day25Sample("..\\..\\Day25Sample.txt");
	std::string Day25Input("..\\..\\Day25Input.txt");
	std::cout << "Day25Part1Sample: " << Day25Part1(Day25Sample) << std::endl;
	std::cout << "Day25Part1: " << Day25Part1(Day25Input) << std::endl;
	std::cout << "Day25Part2Sample: " << Day25Part2(Day25Sample, true) << std::endl;
	std::cout << "Day25Part2: " << Day25Part2(Day25Input) << std::endl;
	//*/

	std::cin.get();

	return 0;
}