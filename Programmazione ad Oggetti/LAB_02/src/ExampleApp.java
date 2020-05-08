import hydraulic.*;

public class ExampleApp {

	public static void main(String args[]){
		
		HSystem s = new HSystem();
	
		// 1) the elements of the system are defined and added
		Source src = new Source("Src");
		s.addElement(src);
		Tap r = new Tap("R");
		s.addElement(r);
		Split t = new Split("T");
		s.addElement(t);
		Sink s1 = new Sink("sink A");
		s.addElement(s1);
		Sink s2 = new Sink("sink B");
		s.addElement(s2);

		Source source1 = new Source("Source1");
		s.addElement(source1);
		Tap tap1 = new Tap("Tap1");
		s.addElement(tap1);
		Tap tap2 = new Tap("Tap2");
		s.addElement(tap2);
		Tap tap3 = new Tap("Tap3");
		s.addElement(tap3);
		Split split1 = new Split("Split1");
		s.addElement(split1);
		Split split2 = new Split("Split2");
		s.addElement(split2);
		Split split3 = new Split("Split3");
		s.addElement(split3);
		Sink sink1 = new Sink("Sink1");
		s.addElement(sink1);
		Sink sink2 = new Sink("Sink2");
		s.addElement(sink2);
		Sink sink3 = new Sink("Sink3");
		s.addElement(sink3);
		Sink sink4 = new Sink("Sink4");
		s.addElement(sink4);
		
		// 2) elements are then connected
		src.connect(r);
		r.connect(t);
		t.connect(s1,0);
		t.connect(s2,1);
		
		source1.connect(tap1);
		tap1.connect(split1);
		split1.connect(tap2, 0);
		split1.connect(tap3, 1);
		tap2.connect(split2);
		split2.connect(split3, 0);
		split3.connect(sink1,0);
		split3.connect(sink2, 1);
		split2.connect(sink3, 1);
		tap3.connect(sink4);
		
		// 3) simulation parameters are then defined
		src.setFlow(20);
		r.setOpen(true);
		
		source1.setFlow(50);
		tap1.setOpen(true);
		tap2.setOpen(true);
		tap3.setOpen(false);
		
		// 4) simulation starts
		s.simulate();
		
		// 5) print the system layout
		System.out.println(s.layout());
	}
}
