// global.hpp
#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <vector>

typedef std::pair<std::string, std::string> Rule;
typedef std::vector<Rule> Rules_t;

const std::string Amoeba	 		= "Amoeba";
const std::string Assimilation		= "Assimilation";
const std::string Coagulations		= "Coagulations";
const std::string ConwaysLife		= "ConwaysLife";
const std::string Coral				= "Coral";	
const std::string DayAndNight	 	= "DayAndNight";
const std::string Diamoeba	 		= "Diamoeba";
const std::string DotLife	 		= "DotLife";
const std::string DryLife	 		= "DryLife";
const std::string Fredkin	 		= "Fredkin";
const std::string Gnarl		 		= "Gnarl";	
const std::string HighLife	 		= "HighLife";
const std::string LifeWithoutDeath	= "LifeWithoutDeath";
const std::string LiveFreeOrDie	 	= "LiveFreeOrDie";	
const std::string LongLife			= "LongLife";
const std::string Maze	 			= "Maze";	
const std::string Mazectric	 	 	= "Mazectric";
const std::string Move				= "Move";	
const std::string PseudoLife	 	= "PseudoLife";	
const std::string Replicator		= "Replicator";
const std::string Seeds				= "Seeds";
const std::string Serviettes		= "Serviettes";
const std::string Stains	 		= "Stains";	
const std::string ThirtyFourLife 	= "ThirtyFourLife";
const std::string TwoByTwo	 		= "TwoByTwo";
const std::string Vote				= "Vote";
const std::string VoteFourSlashFive = "VoteFourSlashFive";
const std::string WalledCities		= "WalledCities";

const std::string Amoeba_rulestring              = "1358/357";
const std::string Assimilation_rulestring        = "4567/345";
const std::string Coagulations_rulestring		 = "235678/378";
const std::string ConwaysLife_rulestring		 = "23/3";	
const std::string Coral_rulestring			     = "45678/3";		
const std::string DayAndNight_rulestring	 	 = "34678/3678";
const std::string Diamoeba_rulestring	 		 = "5678/35678";
const std::string DotLife_rulestring	 		 = "023/3";	
const std::string DryLife_rulestring	 		 = "23/37"; 
const std::string Fredkin_rulestring	 		 = "02468/1357";
const std::string Gnarl_rulestring		     	 = "1/1";			
const std::string HighLife_rulestring	 		 = "23/36";	
const std::string LifeWithoutDeath_rulestring	 = "012345678/";	
const std::string LiveFreeOrDie_rulestring	     = "0/2";	 		
const std::string LongLife_rulestring			 = "5/345";	
const std::string Maze_rulestring	 			 = "12345/3";		
const std::string Mazectric_rulestring	 	     = "1234/3";	
const std::string Move_rulestring				 = "245/368";		
const std::string PseudoLife_rulestring	 	     = "238/357";		
const std::string Replicator_rulestring		     = "1357/1357";
const std::string Seeds_rulestring			     = "/2";	 	
const std::string Serviettes_rulestring		     = "/234";	
const std::string Stains_rulestring	 		     = "235678/3678";	
const std::string ThirtyFourLife_rulestring 	 = "34/34";	
const std::string TwoByTwo_rulestring	 	     = "125/36";	
const std::string Vote_rulestring				 = "45678/5678";
const std::string VoteFourSlashFive_rulestring   = "35678/4678";
const std::string WalledCities_rulestring		 = "2345/45678";

const Rule Amoeba_rule            = std::make_pair( Amoeba,            Amoeba_rulestring            );
const Rule Assimilation_rule      = std::make_pair( Assimilation,      Assimilation_rulestring      );
const Rule Coagulations_rule      = std::make_pair( Coagulations,      Coagulations_rulestring		);
const Rule ConwaysLife_rule       = std::make_pair( ConwaysLife,       ConwaysLife_rulestring		);
const Rule Coral_rule             = std::make_pair( Coral,             Coral_rulestring			    );	
const Rule DayAndNight_rule       = std::make_pair( DayAndNight,       DayAndNight_rulestring	 	);
const Rule Diamoeba_rule          = std::make_pair( Diamoeba,          Diamoeba_rulestring	 		);
const Rule DotLife_rule           = std::make_pair( DotLife,           DotLife_rulestring	 		);
const Rule DryLife_rule           = std::make_pair( DryLife,           DryLife_rulestring	 		);
const Rule Fredkin_rule           = std::make_pair( Fredkin,           Fredkin_rulestring	 		);
const Rule Gnarl_rule             =	std::make_pair( Gnarl,             Gnarl_rulestring		     	);	
const Rule HighLife_rule          = std::make_pair( HighLife,          HighLife_rulestring	 		);
const Rule LifeWithoutDeath_rule  = std::make_pair( LifeWithoutDeath,  LifeWithoutDeath_rulestring	);
const Rule LiveFreeOrDie_rule     = std::make_pair( LiveFreeOrDie,     LiveFreeOrDie_rulestring	    );	
const Rule LongLife_rule          = std::make_pair( LongLife,          LongLife_rulestring			);
const Rule Maze_rule              = std::make_pair( Maze,              Maze_rulestring	 			);	
const Rule Mazectric_rule         = std::make_pair( Mazectric,         Mazectric_rulestring	 	    );
const Rule Move_rule              = std::make_pair( Move,              Move_rulestring				);	
const Rule PseudoLife_rule        = std::make_pair( PseudoLife,        PseudoLife_rulestring	 	);	
const Rule Replicator_rule        = std::make_pair( Replicator,        Replicator_rulestring		);
const Rule Seeds_rule             = std::make_pair( Seeds,             Seeds_rulestring			    );
const Rule Serviettes_rule        = std::make_pair( Serviettes,        Serviettes_rulestring		);
const Rule Stains_rule            = std::make_pair( Stains,            Stains_rulestring	 		);	
const Rule ThirtyFourLife_rule    = std::make_pair( ThirtyFourLife,    ThirtyFourLife_rulestring 	);
const Rule TwoByTwo_rule          = std::make_pair( TwoByTwo,          TwoByTwo_rulestring	 	    );
const Rule Vote_rule              = std::make_pair( Vote,              Vote_rulestring				);
const Rule VoteFourSlashFive_rule = std::make_pair( VoteFourSlashFive, VoteFourSlashFive_rulestring );
const Rule WalledCities_rule      = std::make_pair( WalledCities,      WalledCities_rulestring		);

// Commmon rulestrings in the form S/B - "Survival/Birth"
namespace RuleStrings{

	const Rules_t rules {
		Amoeba_rule,         
		Assimilation_rule,     
		Coagulations_rule,    
		ConwaysLife_rule,    
		Coral_rule,            
		DayAndNight_rule,      
		Diamoeba_rule,         
		DotLife_rule,          
		DryLife_rule,          
		Fredkin_rule,          
		Gnarl_rule,            
		HighLife_rule,         
		LifeWithoutDeath_rule, 
		LiveFreeOrDie_rule,    
		LongLife_rule,         
		Maze_rule,             
		Mazectric_rule,        
		Move_rule,             
		PseudoLife_rule,       
		Replicator_rule,       
		Seeds_rule,            
		Serviettes_rule,       
		Stains_rule,           
		ThirtyFourLife_rule,   
		TwoByTwo_rule,         
		Vote_rule,             
		VoteFourSlashFive_rule,
		WalledCities_rule     
	};
}

// Log files definitions
namespace logFiles{
	
	const std::string logFileName = "logfile.log"; 
};

#endif