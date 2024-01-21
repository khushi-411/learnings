class <lambda>(torch.nn.Module):
    def forward(self, arg0_1: "u8[1, 8]", arg1_1: "u8[8390, 8]"):
        # File: /home/khushi/Documents/pt2_dev/learnings/pytorch/profile/../doc_codes/eg.py:6 in foo1, code: a = torch.neg(x1)
        neg: "u8[1, 8]" = torch.ops.aten.neg.default(arg0_1);  arg0_1 = None
        
        # File: /home/khushi/Documents/pt2_dev/learnings/pytorch/profile/../doc_codes/eg.py:7 in foo1, code: b = torch.maximum(x2, a)
        maximum: "u8[8390, 8]" = torch.ops.aten.maximum.default(arg1_1, neg);  arg1_1 = neg = None
        return (maximum,)
        