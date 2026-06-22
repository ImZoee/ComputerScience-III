create table produs (
  cod_produs        number primary key,
  denumire_produs   varchar2(80) not null,
  cantitate_produs  number default 0 check (cantitate_produs >= 0),
  pretc             number(10,2) not null check (pretc >= 0)
);

create table material (
  cod_material      number primary key,
  denumire_material varchar2(80) not null,
  um                varchar2(10) not null,
  pret_unit         number(10,2) not null check (pret_unit >= 0)
);

create table structura (
  cod_produs            number not null,
  cod_material          number not null,
  cant_mat_pt_un_prod   number(10,3) not null check (cant_mat_pt_un_prod > 0),
  constraint pk_structura primary key (cod_produs, cod_material),
  constraint fk_struct_prod foreign key (cod_produs) references produs(cod_produs),
  constraint fk_struct_mat foreign key (cod_material) references material(cod_material)
);

create table plan_product (
  cod_produs number not null,
  nr_buc     number not null check (nr_buc > 0),
  constraint pk_plan_product primary key (cod_produs),
  constraint fk_plan_prod foreign key (cod_produs) references produs(cod_produs)
);

create sequence seq_produs start with 1 increment by 1 nocache;
create sequence seq_material start with 100 increment by 1 nocache;

insert into produs (cod_produs, denumire_produs, cantitate_produs, pretc)
values (seq_produs.nextval, 'Bicicleta urbana', 0, 1500);
insert into produs values (seq_produs.nextval, 'Scaun ergonomic', 0, 450);
insert into produs values (seq_produs.nextval, 'Masuta cafea', 0, 320);

insert into material (cod_material, denumire_material, um, pret_unit)
values (seq_material.nextval, 'Cadru aluminiu', 'buc', 320);
insert into material values (seq_material.nextval, 'Roti 28 inchi', 'set', 260);
insert into material values (seq_material.nextval, 'Sistem franare disc', 'set', 180);
insert into material values (seq_material.nextval, 'Lemn fag', 'kg', 18);
insert into material values (seq_material.nextval, 'Burete densitate medie', 'kg', 22);
insert into material values (seq_material.nextval, 'Textil rezistent', 'm2', 30);
insert into material values (seq_material.nextval, 'Suruburi inox', 'set', 12);
insert into material values (seq_material.nextval, 'Lac transparent', 'l', 25);
insert into material values (seq_material.nextval, 'Grund lemn', 'l', 28);

insert into structura values (1, 100, 1);
insert into structura values (1, 101, 1);
insert into structura values (1, 102, 1);
insert into structura values (1, 107, 1);
insert into structura values (2, 104, 2.5);
insert into structura values (2, 105, 1);
insert into structura values (2, 106, 1.5);
insert into structura values (2, 107, 1);
insert into structura values (3, 104, 4);
insert into structura values (3, 107, 1.5);
insert into structura values (3, 108, 0.5);

insert into plan_product values (1, 250);
insert into plan_product values (2, 500);
insert into plan_product values (3, 350);

commit;

select
  row_number() over(order by m.denumire_material, s.cod_produs) as nr_crt,
  m.denumire_material,
  m.cod_material,
  p.nr_buc as nr_buc,
  s.cant_mat_pt_un_prod * p.nr_buc as cantitate_totala,
  (s.cant_mat_pt_un_prod * p.nr_buc) * m.pret_unit as valoare
from plan_product p
join structura s on s.cod_produs = p.cod_produs
join material m on m.cod_material = s.cod_material
order by m.denumire_material, s.cod_produs;

select
  row_number() over(order by m.denumire_material) as nr_crt,
  m.denumire_material,
  m.cod_material,
  sum(s.cant_mat_pt_un_prod * p.nr_buc) as cantitate_totala,
  sum((s.cant_mat_pt_un_prod * p.nr_buc) * m.pret_unit) as valoare
from plan_product p
join structura s on s.cod_produs = p.cod_produs
join material m on m.cod_material = s.cod_material
group by m.denumire_material, m.cod_material
order by m.denumire_material;

create or replace function fn_valoare_materiale_produs(p_cod_produs in number, p_use_plan in boolean default false)
  return number
as
  v_total number := 0;
begin
  if p_use_plan then
    select nvl(sum(s.cant_mat_pt_un_prod * m.pret_unit * p.nr_buc), 0)
      into v_total
      from structura s
      join material m on m.cod_material = s.cod_material
      join plan_product p on p.cod_produs = s.cod_produs
     where s.cod_produs = p_cod_produs;
  else
    select nvl(sum(s.cant_mat_pt_un_prod * m.pret_unit), 0)
      into v_total
      from structura s
      join material m on m.cod_material = s.cod_material
     where s.cod_produs = p_cod_produs;
  end if;
  return v_total;
end;

create or replace procedure prd_top_materiale(
  p_cod_produs out produs.cod_produs%type,
  p_denumire   out produs.denumire_produs%type,
  p_nr_mat     out number,
  p_val_mat    out number
) is
  v_cod_top produs.cod_produs%type;
begin
  select cod_produs
    into v_cod_top
    from (
      select s.cod_produs,
             count(*) as nr_mat,
             sum(s.cant_mat_pt_un_prod * m.pret_unit) as val_mat,
             row_number() over(order by count(*) desc, sum(s.cant_mat_pt_un_prod * m.pret_unit) desc, cod_produs) rn
        from structura s
        join material m on m.cod_material = s.cod_material
       group by s.cod_produs
    )
   where rn = 1;

  select p.cod_produs, p.denumire_produs, count(*), sum(s.cant_mat_pt_un_prod * m.pret_unit)
    into p_cod_produs, p_denumire, p_nr_mat, p_val_mat
    from produs p
    join structura s on s.cod_produs = p.cod_produs
    join material m on m.cod_material = s.cod_material
   where p.cod_produs = v_cod_top
   group by p.cod_produs, p.denumire_produs;

  dbms_output.put_line('Produs cu cele mai multe materiale: cod=' || p_cod_produs || ', denumire=' || p_denumire || ', nr_mat=' || p_nr_mat || ', val_mat=' || p_val_mat);
end;

declare
  cursor c_materiale_nefolosite is
    select m.cod_material, m.denumire_material
      from material m
     where not exists (select 1 from structura s where s.cod_material = m.cod_material);
  v_total_distinct number;
  v_nefolosite number := 0;
  v_dummy c_materiale_nefolosite%rowtype;
begin
  select count(distinct cod_material) into v_total_distinct from structura;

  dbms_output.put_line('Materiale distincte in structura: ' || v_total_distinct);
  dbms_output.put_line('Lista materiale nefolosite:');

  open c_materiale_nefolosite;
  loop
    fetch c_materiale_nefolosite into v_dummy;
    exit when c_materiale_nefolosite%notfound;
    v_nefolosite := v_nefolosite + 1;
    dbms_output.put_line('  - ' || v_dummy.cod_material || ' / ' || v_dummy.denumire_material);
  end loop;
  close c_materiale_nefolosite;

  dbms_output.put_line('Numar materiale nefolosite: ' || v_nefolosite);
end;

begin
  for r in (select p.cod_produs, p.denumire_produs, nvl(pp.nr_buc, 0) as nr_buc
              from produs p
              left join plan_product pp on pp.cod_produs = p.cod_produs
             order by p.cod_produs) loop
    dbms_output.put_line('Produs ' || r.cod_produs || ' - ' || r.denumire_produs ||
                         ': val/unit=' || fn_valoare_materiale_produs(r.cod_produs) ||
                         ', val/plan=' || fn_valoare_materiale_produs(r.cod_produs, true));
  end loop;
end;

begin
  null;
end;

declare
  v_cod produs.cod_produs%type;
  v_denumire produs.denumire_produs%type;
  v_nr_mat number;
  v_val_mat number;
begin
  prd_top_materiale(v_cod, v_denumire, v_nr_mat, v_val_mat);
  dbms_output.put_line('Top produs (OUT): cod=' || v_cod || ', denumire=' || v_denumire || ', nr_mat=' || v_nr_mat || ', val_mat=' || v_val_mat);
end;
