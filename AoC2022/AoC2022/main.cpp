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
	IntVector2D operator+( const IntVector2D& Other ) const { return IntVector2D( X + Other.X, Y + Other.Y ); }
	IntVector2D operator-( const IntVector2D& Other ) const { return IntVector2D( X - Other.X, Y - Other.Y ); }
	IntVector2D operator*( const IntVector2D& Other ) const { return IntVector2D( X * Other.X, Y * Other.Y ); }
	IntVector2D operator*( int Scale ) const { return IntVector2D( X * Scale, Y * Scale ); }
	IntVector2D operator/( const IntVector2D& Other ) const { return IntVector2D( Other.X ? X / Other.X : 0, Other.Y ? Y / Other.Y : 0 ); }
	IntVector2D operator/( int Scale ) const { return IntVector2D( Scale ? X / Scale : 0, Scale ? Y / Scale : 0 ); }

	// Ew
	int Size() const { return (int)std::sqrtf( (float)(X * X + Y * Y )); }

	int X;
	int Y;
}; 

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

int Day12Part1( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::string> InstructionStack;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
	}

	myfile.close();

	return 0;
}

int Day12Part2( const std::string& Filename, bool bShouldPrint = false )
{
	std::ifstream myfile;
	myfile.open( Filename );

	std::vector<std::string> InstructionStack;

	while ( myfile.good() )
	{
		char line[4096];
		myfile.getline( line, 4096 );
		std::string Line( line );
	}

	myfile.close();

	return 0;
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
	//*/

	std::string Day12Sample( "..\\..\\Day12Sample.txt" );
	std::string Day12Input( "..\\..\\Day12Input.txt" );
	std::cout << "Day12Part1Sample: " << Day12Part1( Day12Sample ) << std::endl;
	std::cout << "Day12Part1: " << Day12Part1( Day12Input ) << std::endl;
	std::cout << "Day12Part2Sample: " << Day12Part2( Day12Sample ) << std::endl;
	std::cout << "Day12Part2: " << Day12Part2( Day12Input ) << std::endl;

	std::cin.get();

	return 0;
}