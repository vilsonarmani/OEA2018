

procedure TfrmDrag1.Button1Click(Sender: TObject);
var i      : Byte;
    inicio,
    meio, 
    fim    : Extended;
    recCep :TCep;
begin
  if not qry.active then qry.open;
  inicio := 0;

  fim    := qry.RecordCount; // equivalente ao SEEK_END e ftell
   
  qry.first; //equivalente ao rewind
 
  i := 0;

  while inicio <= fim do
  begin
     inc(i);

     meio   := (inicio + fim) /2;

     qry.RecNo := Trunc(meio); 

     if qry.FieldByName('CEP').AsString = edtCep.text then
     begin
       (*) preferi utilizar a propria string nesse exemplo a utilizar um record. record seria utilizado no arquivo cep ordenado.
       (*)
       ShowMessage('CEP:        '+ qry.Fields[0].AsString +#13+  
                   'Logradouro: '+ qry.Fields[1].AsString +#13+
                   'De/Até:     '+ qry.Fields[2].AsString +#13+
                   'Cidade:     '+ qry.Fields[3].AsString +#13+
                   'Bairro:     '+ qry.Fields[4].AsString +#13+
                   'UF:         '+ qry.Fields[5].AsString +#13+#13+
                   'Foram dados '+IntToStr(i)+' passos para encontrar o Cep informado!'  );
       exit;
     end;

     if StrToInt(edtCep.text) < qry.FieldByName('CEP').AsInteger then {The magic Is here!}
       fim  := meio + 1 
     else inicio := meio -1;

  end;
end;

