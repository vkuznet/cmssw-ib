DROP TABLE SM_INSTANCES;

CREATE TABLE SM_INSTANCES (
   RUNNUMBER          NUMBER(10)      --CREATE (NEEDED BY ALL)
  ,HOSTNAME           VARCHAR2(100)
  ,INSTANCE           NUMBER(5)
  ,SETUPLABEL         VARCHAR2(100)
  ,N_CREATED          NUMBER(10)
  ,N_INJECTED         NUMBER(10)
  ,N_NEW              NUMBER(10)
  ,N_COPIED           NUMBER(10)
  ,N_CHECKED          NUMBER(10)
  ,N_INSERTED         NUMBER(10)
  ,N_REPACKED         NUMBER(10)
  ,N_NOTREPACKED      NUMBER(10)
  ,N_DELETED          NUMBER(10)
  ,N_UNACCOUNT        NUMBER(10)
  ,START_WRITE_TIME   TIMESTAMP(6)
  ,LAST_WRITE_TIME    TIMESTAMP(6)
  ,DISKFULL           NUMBER(10)
  ,CONSTRAINT PK_RNIns PRIMARY KEY (RUNNUMBER, HOSTNAME, INSTANCE)
);
