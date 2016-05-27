function openfile(filename,fnum)
    disp(filename);printf("\n");
    hol=holread(filename);
    a=angle(hol)+pi;
    a=a./max(max(a));
    qa=round(a*3);
	imwrite(qa,sprintf('holframes/frame%05d.png',fnum),8);
    end
% Reading a hologram file
% Modified 8/18/00
%% tjn 03 III 2005
%% tjn 20 III 2012, call error if file not exist

function A=holread(name,ext);

if (nargin < 2)
  ext = 'hol';
end

fname = [name,'.',ext];
%%CM
f1=fopen(["Holograms/",fname],'r');
if f1==-1
   error(['The file ''',fname,''' does not exist.'])
   return
end
t=fread(f1,1,'int8');
Ny=fread(f1,1,'uint32'); %- was uint
Nx=fread(f1,1,'uint32'); %- was uint
if t==1
   A=fread(f1,[Ny,Nx],'double');
   s=sprintf('Reading %dx%d real',Nx,Ny);
elseif t==2
   Ar=fread(f1,[Ny,Nx],'double');
   Ai=fread(f1,[Ny,Nx],'double');
   A=Ar+j*Ai;
   s=sprintf('Reading %dx%d complex',Ny,Nx);
else
   error(['Unknown header byte of ',int2str(t),'.']);
end
disp([s,' from ',fname]);
fclose(f1);
end
