def annotate(minefield):
    reveal_field=[]
    if len(minefield)==0: 
        return reveal_field
    not_valid=[1 for line in minefield if len(line)!=len(minefield[0])]
    if not_valid!=[]:
        raise ValueError("The board is invalid with current input.")
    mines_count=[[[char,0]for char in line] for line in minefield
    if len(minefield)==1:
        reveal_field=[RowToStr(DoRow(mines_count[0]))]
    else:
        for i in range(len(mines_count)-1):
            row_next_row=RowRowCount(mines_count[i],mines_count[i+1])
            reveal_field.append(RowToStr(row_next_row[0]))
            mines_count[i+1]=row_next_row[1]
            if i+1==len(mines_count)-1:
                last_row=DoRow(mines_count[i+1])
                reveal_field.append(RowToStr(last_row))
    return reveal_field

        
def RowToStr(l):
    st=""
    for k in l:
        if k[0]!="*" and k[0]!=" ":
            raise ValueError("The board is invalid with current input.")
        if k[0]=="*": st+="*"
        else:
            if k[1]==0: st+=" "
            else: st+=str(k[1])
    return st

        
def DoRow(l0):
    for j, c in enumerate(l0):
        if c[0]=="*":
            l0[j][1]+=1
            if j>0:
                l0[j-1][1]+=1
            if j<len(l0)-1:
                l0[j+1][1]+=1
    return l0

        

def RowRowCount(l1,l2):
    for i, c1 in enumerate(l1):
        if c1[0]=="*":
            l2[i][1]+=1
            if i>0:
                l1[i-1][1]+=1
                l2[i-1][1]+=1
            if i<len(l1)-1:
                l1[i+1][1]+=1
                l2[i+1][1]+=1
    for j, c2 in enumerate(l2):
        if c2[0]=="*":
            l1[j][1]+=1
            if j>0:
                l1[j-1][1]+=1
            if j<len(l2)-1:
                l1[j+1][1]+=1
    return [l1 ,l2]