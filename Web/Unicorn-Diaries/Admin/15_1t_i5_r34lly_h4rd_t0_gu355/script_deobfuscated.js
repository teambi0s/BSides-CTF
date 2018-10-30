$("#c_submit").click(function(event) {
    event.preventDefault();
    var u = $("#cuser").val();
    var u1 = u.slice(0,4);
    u1 = u1.split("").reverse().join("");
    u1 = "0x" + u1.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var u2 = u.slice(4, 8);
    u2 = u2.split("").reverse().join("");
    u2 = "0x" + u2.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var u3 = u.slice(8, 12);
    u3 = u3.split("").reverse().join("");
    u3 = "0x" + u3.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var u4 = u.slice(12, 16);
    u4 = u4.split("").reverse().join("");
    u4 = "0x" + u4.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var u5 = u.slice(16, 19);
    u5 = u5.split("").reverse().join("");
    u5 = "0x" + u5.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    
    var p = $("#cpass").val();
    var p1 = p.slice(0,4);
    p1 = p1.split("").reverse().join("");
    p1 = "0x" + p1.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var p2 = p.slice(4, 8);
    p2 = p2.split("").reverse().join("");
    p2 = "0x" + p2.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var p3 = p.slice(8, 12);
    p3 = p3.split("").reverse().join("");
    p3 = "0x" + p3.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var p4 = p.slice(12, 16);
    p4 = p4.split("").reverse().join("");
    p4 = "0x" + p4.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    var p5 = p.slice(16, 19);
    p5 = p5.split("").reverse().join("");
    p5 = "0x" + p5.split("").map((x) => x.charCodeAt(0).toString(16)).join("")
    
    var e = new uc.Unicorn(uc.ARCH_X86, uc.MODE_32);
    var addr = 0x8048000;
    var code = [0xbf, 0x31, 0x34, 0x6d, 0x37, 0x39, 0xf8, 0x75, 0x2b, 0xbf, 0x68, 
                0x33, 0x61, 0x34, 0x64, 0xfb, 0x75, 0x22, 0xbf, 0x6d, 0x31, 0x6e, 
                0x31, 0x39, 0xf9, 0x75, 0x19, 0xbf, 0x35, 0x37, 0x72, 0x34, 0x39, 
                0xfa, 0x75, 0x10, 0xbf, 0x74, 0x30, 0x72, 0x00, 0x39, 0xfe, 0x75, 
                0x07, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xeb, 0x05, 0xb8, 0x00, 0x00, 
                0x00, 0x00];
    e.reg_write_i32(uc.X86_REG_EAX, u1);
    e.reg_write_i32(uc.X86_REG_EBX, u2);
    e.reg_write_i32(uc.X86_REG_ECX, u3);
    e.reg_write_i32(uc.X86_REG_EDX, u4);
    e.reg_write_i32(uc.X86_REG_ESI, u5);
    e.mem_map(addr, 4096, uc.PROT_ALL);
    e.mem_write(addr, code);
    e.emu_start(addr, addr + code.length);
    var t = e.reg_read_i32(uc.X86_REG_EAX);
    if (t) {
	    var e = new uc.Unicorn(uc.ARCH_X86, uc.MODE_32);
	    var addr = 0x08048000;
	    var code = [0x81, 0xc6, 0x69, 0x61, 0x6d, 0x74, 0x81, 0xc6, 0x07, 0x06, 
                    0x05, 0x04, 0x81, 0xfe, 0xd3, 0xd6, 0xe0, 0xdf, 0x75, 0x55, 
                    0x40, 0x81, 0xc3, 0x68, 0x65, 0x61, 0x64, 0x81, 0xc3, 0x03, 
                    0x02, 0x01, 0x00, 0x81, 0xfb, 0xdd, 0xdb, 0xdc, 0x98, 0x75, 
                    0x40, 0x40, 0x81, 0xc1, 0x6d, 0x69, 0x6e, 0x69, 0x81, 0xc1, 
                    0x0f, 0x0e, 0x0d, 0x0c, 0x81, 0xf9, 0xf0, 0xdf, 0xe0, 0xe5, 
                    0x75, 0x2b, 0x40, 0x81, 0xc2, 0x73, 0x74, 0x72, 0x61, 0x81, 
                    0xc2, 0x0b, 0x0a, 0x09, 0x08, 0x81, 0xfa, 0xdf, 0xf1, 0x9f, 
                    0xe0, 0x75, 0x16, 0x40, 0x81, 0xc5, 0x74, 0x6f, 0x72, 0x00, 
                    0x81, 0xc5, 0x17, 0x16, 0x15, 0x00, 0x81, 0xfd, 0xbb, 0xf7, 
                    0xcb, 0x00, 0x75, 0x01, 0x40];
	    e.reg_write_i32(uc.X86_REG_ESI, p1);
	    e.reg_write_i32(uc.X86_REG_EBX, p2);
	    e.reg_write_i32(uc.X86_REG_ECX, p3);
	    e.reg_write_i32(uc.X86_REG_EDX, p4);
	    e.reg_write_i32(uc.X86_REG_EBP, p5);
	    e.mem_map(addr, 4096, uc.PROT_ALL);
	    e.mem_write(addr, code);
	    e.emu_start(addr, addr + code.length);
	    var check = e.reg_read_i32(uc.X86_REG_EAX);
        if (check == 5) {
            if (document.location.href.indexOf("?p=") == -1) {
                document.location = document.location + "/../" + u + ".html";
            }	
        }
        else{
            alert('Wrong credentials, sorry');
        }
    }
    else{
        alert('Wrong credentials, sorry');
    }
});
