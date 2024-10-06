/*
    Anti Car Push (Crasher) | Lasho4 changed to include
    (C) don't know code author
*/

enum (+=1)
{
    ACP_VEHICLE_USE_TYPE_UNFROZEN,
    ACP_VEHICLE_USE_TYPE_UNOCCUPIED,
    ACP_VEHICLE_USE_TYPE_HASDRIVER
}

enum e_ucp_vehicle
{
    Float:ucp_vPosX,
    Float:ucp_vPosY,
    Float:ucp_vPosZ,
    Float:ucp_vZAngle,
    ucp_vUsed
}
new ucp_Vehicle[MAX_VEHICLES][e_ucp_vehicle];

public OnPlayerExitVehicle(playerid, vehicleid)
{
    ucp_Vehicle[vehicleid][ucp_vUsed] = ACP_VEHICLE_USE_TYPE_UNFROZEN;
    #if defined acp_OnPlayerExitVehicle
		return acp_OnPlayerExitVehicle(playerid, vehicleid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle acp_OnPlayerExitVehicle
#if defined acp_OnPlayerExitVehicle
	forward acp_OnPlayerExitVehicle(playerid, vehicleid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        ucp_Vehicle[GetPlayerVehicleID(playerid)][ucp_vUsed] = ACP_VEHICLE_USE_TYPE_HASDRIVER;
    }
    #if defined acp_OnPlayerStateChange
		return acp_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange acp_OnPlayerStateChange
#if defined acp_OnPlayerStateChange
	forward acp_OnPlayerStateChange(playerid, newstate, oldstate);
#endif


public OnVehicleSpawn(vehicleid)
{
    GetVehiclePos(vehicleid,ucp_Vehicle[vehicleid][ucp_vPosX],ucp_Vehicle[vehicleid][ucp_vPosY],ucp_Vehicle[vehicleid][ucp_vPosZ]);
    GetVehicleZAngle(vehicleid,ucp_Vehicle[vehicleid][ucp_vZAngle]);
    ucp_Vehicle[vehicleid][ucp_vUsed] = ACP_VEHICLE_USE_TYPE_UNOCCUPIED;
    #if defined acp_OnVehicleSpawn
		return acp_OnVehicleSpawn(vehicleid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn acp_OnVehicleSpawn
#if defined acp_OnVehicleSpawn
	forward acp_OnVehicleSpawn(vehicleid);
#endif

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
    if(acp_GetVehicleSpeed(vehicleid) != 0)
        if(ucp_Vehicle[vehicleid][ucp_vUsed] != ACP_VEHICLE_USE_TYPE_UNFROZEN)
            ucp_Vehicle[vehicleid][ucp_vUsed] = ACP_VEHICLE_USE_TYPE_UNFROZEN;
    if(ucp_Vehicle[vehicleid][ucp_vUsed] == ACP_VEHICLE_USE_TYPE_UNFROZEN)
    {
        if(acp_GetVehicleSpeed(vehicleid) == 0)
        {
            GetVehiclePos(vehicleid,ucp_Vehicle[vehicleid][ucp_vPosX],ucp_Vehicle[vehicleid][ucp_vPosY],ucp_Vehicle[vehicleid][ucp_vPosZ]);
            GetVehicleZAngle(vehicleid,ucp_Vehicle[vehicleid][ucp_vZAngle]);
            ucp_Vehicle[vehicleid][ucp_vUsed] = ACP_VEHICLE_USE_TYPE_UNOCCUPIED;
        }
    }
    if(ucp_Vehicle[vehicleid][ucp_vUsed] == 1)
    {
        #if defined foreach
        foreach(new i:Player)
        {
        #else
        for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
        {
            if(!IsPlayerConnected(i)) continue;
        #endif
                if(GetPlayerState(i) == PLAYER_STATE_ONFOOT) 
                    if(IsPlayerInRangeOfPoint(i,3.2,ucp_Vehicle[vehicleid][ucp_vPosX],ucp_Vehicle[vehicleid][ucp_vPosY],ucp_Vehicle[vehicleid][ucp_vPosZ]))
                    {
                         SetVehiclePos(vehicleid,ucp_Vehicle[vehicleid][ucp_vPosX],ucp_Vehicle[vehicleid][ucp_vPosY],ucp_Vehicle[vehicleid][ucp_vPosZ]);
                         SetVehicleZAngle(vehicleid,ucp_Vehicle[vehicleid][ucp_vZAngle]);
                    }
        }
    }
    #if defined acp_OnUnoccupiedVehicleUpdate
		return acp_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnUnoccupiedVehicleUpdate
	#undef OnUnoccupiedVehicleUpdate
#else
	#define _ALS_OnUnoccupiedVehicleUpdate
#endif
#define OnUnoccupiedVehicleUpdate acp_OnUnoccupiedVehicleUpdate
#if defined acp_OnUnoccupiedVehicleUpdate
	forward acp_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z);
#endif

stock acp_GetVehicleSpeed(vehicleid, bool:kmh = true)
{
    new
        Float:xx,
        Float:yy,
        Float:zz,
        Float:vehSpeed;
   
    GetVehicleVelocity(vehicleid,xx,yy,zz);
    vehSpeed  = floatsqroot((xx * xx) + (yy * yy) + (zz * zz));
    return kmh ? floatround((vehSpeed * 195.12)) : floatround((vehSpeed * 136.66667));
}