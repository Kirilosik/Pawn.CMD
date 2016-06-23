// Pawn.CMD plugin by urShadow

#if !defined __cplusplus
	#if defined _pawncmd_included
	  #endinput
	#endif
	#define _pawncmd_included
#endif

#define PAWNCMD_INCLUDE_VERSION 30

#if !defined __cplusplus
	public _pawncmd_version = PAWNCMD_INCLUDE_VERSION;
	#pragma unused _pawncmd_version

	native PC_Init(bool:is_gamemode);
	native PC_RegAlias(const cmd[], const alias[], ...);
	native PC_SetFlags(const cmd[], flags);
	native PC_GetFlags(const cmd[], &flags);
	native PC_EmulateCommand(playerid, const cmdtext[]);
	native PC_RenameCommand(const name[], const newname[]);
	native PC_DeleteCommand(const name[]);

	#if defined OnPlayerCommandReceived
		forward OnPlayerCommandReceived(playerid, cmd[], params[], flags);
	#endif

	#if defined OnPlayerCommandPerformed
		forward OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags);
	#endif

	#define cmd:%0(%1) \
		forward pc_cmd_%0(%1); \
		public pc_cmd_%0(%1)
		
	#define alias:%0(%1); \
		forward pc_alias_%0(); \
		public pc_alias_%0() \
			PC_RegAlias(#%0, %1);
			
	#define flags:%0(%1); \
		forward pc_flags_%0(); \
		public pc_flags_%0() \
			PC_SetFlags(#%0, %1);
		
	#define CMD cmd	
	#define COMMAND cmd
	
	#define callcmd::%0(%1) \
		pc_cmd_%0(%1)

	#if !defined isnull
		#define isnull(%1) \
			((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
	#endif

	#if defined FILTERSCRIPT
		public OnFilterScriptInit()
		{		
			PC_Init(false);	
			
			#if defined pawncmd_OnFilterScriptInit
				pawncmd_OnFilterScriptInit();
			#endif
			
			return 1;
		}
		 
		#if defined _ALS_OnFilterScriptInit
			#undef OnFilterScriptInit
		#else
			#define _ALS_OnFilterScriptInit
		#endif

		#define OnFilterScriptInit pawncmd_OnFilterScriptInit

		#if defined pawncmd_OnFilterScriptInit
			forward pawncmd_OnFilterScriptInit();
		#endif
	#else
		public OnGameModeInit()
		{	
			PC_Init(true);
			
			#if defined pawncmd_OnGameModeInit
				pawncmd_OnGameModeInit();
			#endif
			
			return 1;
		}
		 
		#if defined _ALS_OnGameModeInit
			#undef OnGameModeInit
		#else
			#define _ALS_OnGameModeInit
		#endif

		#define OnGameModeInit pawncmd_OnGameModeInit

		#if defined pawncmd_OnGameModeInit
			forward pawncmd_OnGameModeInit();
		#endif
	#endif
#endif